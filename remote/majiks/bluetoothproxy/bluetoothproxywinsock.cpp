#include "bluetoothproxywinsock.h"

#ifdef BLUETOOTH_USING_WINSOCK
#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>

#include <QDebug>
#include <QMutexLocker>

#include <memory>

// {B62C4E8D-62CC-404b-BBBF-BF3E3BBB1374}
DEFINE_GUID(g_guidServiceClass, 0xb62c4e8d, 0x62cc, 0x404b, 0xbb, 0xbf, 0xbf, 0x3e, 0x3b, 0xbb, 0x13, 0x74);
QString getLatestError(int errorCode = 0)
{
    static TCHAR errmsg[512];
    int er = ((errorCode == 0) ? WSAGetLastError() : errorCode);

    if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, er, 0, errmsg, 511, NULL))
    {
    /* if we fail, call ourself to find out why and return that error */
        return getLatestError();
    }

    return QString("Error %1: ").arg(er) + QString::fromWCharArray(errmsg);
}

BluetoothProxyWinsock::BluetoothProxyWinsock(QObject *parent): BluetoothProxy(parent)
{
    m_socket = INVALID_SOCKET;

    m_listenerThread = new WorkerThread(this);

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);

    if(WSAStartup( wVersionRequested, &wsaData ) != NO_ERROR)
    {
        qDebug() << "Couldn't initialize PoS sockets";
    }
    else
        qDebug() << "Winsock2 initializated";
}

BluetoothProxyWinsock::WorkerThread::WorkerThread(BluetoothProxyWinsock* overseer): QThread(overseer),m_running(false),m_overseer(overseer) {}

BluetoothProxyWinsock::~BluetoothProxyWinsock()
{
    WSACleanup();
    qDebug() << "Winsock2 cleaned up";
}


void BluetoothProxyWinsock::connectToHost(const QString& address)
{
    // Will soft-kill the listener thread
    disconnect();

    SOCKADDR_BTH addressStruct = {0};

    WSAStringToAddress((LPTSTR)(address.toStdString().c_str()), AF_BTH, NULL, reinterpret_cast<sockaddr*>(&addressStruct), (LPINT)sizeof(SOCKADDR_BTH));

    addressStruct.addressFamily     = AF_BTH;
    addressStruct.serviceClassId    = g_guidServiceClass;
    addressStruct.port              = 0;

    // Will wait for the listener thread to stop
    QMutexLocker lock(&m_socketMutex);
    if(::connect(m_socket, reinterpret_cast<sockaddr*>(&addressStruct), sizeof(SOCKADDR_BTH)) == SOCKET_ERROR)
    {
        qDebug() << "Socket PoS couldn't connect to " << address;
        qDebug() << "Error: " << getLatestError();
    }
    else
    {
        m_remoteAddress = address;

        // Restart the listener thread
        m_listenerThread->start();
    }

}

QString BluetoothProxyWinsock::remoteAddress() const
{
    return m_remoteAddress;
}

void BluetoothProxyWinsock::disconnect()
{
    m_listenerThread->softKill();
}

void BluetoothProxyWinsock::WorkerThread::softKill()
{
    QMutexLocker lock(&m_runningMutex);
    m_running = false;
}

void BluetoothProxyWinsock::WorkerThread::run()
{
    // We expressely forbit ANY other thread from accessing the socket as long as this routine is running
    QMutexLocker lock(&(m_overseer->m_socketMutex));

    if(m_overseer->m_socket == INVALID_SOCKET)
        return;

    m_overseer->connected(); // 'emit' hack, see https://stackoverflow.com/questions/15176458/how-can-i-emit-a-signal-from-another-class
    qDebug() << "Connected";

    m_runningMutex.lock();
    m_running = true;
    m_runningMutex.unlock();

    bool localRunning = true;;

    do
    {
        receiveAll();

        sendAll();

        m_runningMutex.lock();
        localRunning = m_running;
        m_runningMutex.unlock();
    } while(localRunning);

    closesocket(m_overseer->m_socket);
    m_overseer->m_socket = INVALID_SOCKET;

    m_overseer->m_remoteAddress.clear();

    m_overseer->disconnected(); // 'emit' hack
    qDebug() << "Disconnected";
}

void BluetoothProxyWinsock::WorkerThread::receiveAll()
{
    int bufferSize = 64;

    std::unique_ptr<char> buffer(new char[bufferSize]);
    int pendingDataSize = recv(m_overseer->m_socket, buffer.get(), bufferSize, 0);

    if(pendingDataSize == SOCKET_ERROR || pendingDataSize < 0)
    {
        qDebug() << "PoS socket got an error while reading!";
        qDebug() << "Error: " << getLatestError();
    }
    else
    {
        m_rcvBuffer.append(buffer.get(), pendingDataSize);

        if(bufferSize < pendingDataSize)
        {
            std::unique_ptr<char> buffer2(new char[pendingDataSize - bufferSize]);
            if(recv(m_overseer->m_socket, buffer2.get(), pendingDataSize - bufferSize, 0) == SOCKET_ERROR)
            {
                qDebug() << "PoS socket got an error while reading!";
                qDebug() << "Error: " << getLatestError();
            }
            m_rcvBuffer.append(buffer2.get(), pendingDataSize - bufferSize);
        }
    }

    m_overseer->processData(m_rcvBuffer);
}


void BluetoothProxyWinsock::WorkerThread::sendAll()
{
    QMutexLocker lock(&m_packetQueueMutex);

    while(!m_packetQueue.isEmpty())
    {
        KrabiPacket packet = m_packetQueue.dequeue();

        QByteArray binData = packet.dataByteArray();
        binData.append(0x0D);
        binData.append(0x0A);

        if(send(m_overseer->m_socket, binData.data(), binData.size(), 0) == SOCKET_ERROR)
        {
            qDebug() << "PoS sockets failed to send data!";
        }
    }
}

void BluetoothProxyWinsock::WorkerThread::sendPacket(KrabiPacket packet)
{
    QMutexLocker lock(&m_packetQueueMutex);
    m_packetQueue.enqueue(packet);
}


void BluetoothProxyWinsock::setAdapter(const QString&/* address*/)
{
}

QString BluetoothProxyWinsock::getAdapterAddress()
{
    return QString();
}


QStringList BluetoothProxyWinsock::getAllLocalAdapters()
{
    return QStringList();
}


void BluetoothProxyWinsock::sendData(KrabiPacket& data)
{
    if(!isConnected())
        return;

    m_listenerThread->sendPacket(data);
}

void BluetoothProxyWinsock::scanRemoteDevices()
{
    WSAQUERYSET queryset;
    memset(&queryset, 0, sizeof(WSAQUERYSET));
    queryset.dwSize = sizeof(WSAQUERYSET);
    queryset.dwNameSpace = NS_BTH;

    HANDLE hLookup;
    int result = WSALookupServiceBegin(&queryset, LUP_CONTAINERS, &hLookup);
    if (result!=0)
    {
        qDebug() << "Fail : " << getLatestError();
        return;
    }

    BYTE buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    DWORD bufferLength = sizeof(buffer);
    WSAQUERYSET *pResults = (WSAQUERYSET*)&buffer;
    do
    {
        result = WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_CONTAINERS | LUP_RETURN_ADDR | LUP_FLUSHCACHE | LUP_RETURN_TYPE | LUP_RETURN_BLOB | LUP_RES_SERVICE, &bufferLength, pResults);
        if(result==0)
        {
            LPTSTR s = pResults->lpszServiceInstanceName;

            QString name = QString::fromWCharArray(s);
            qDebug() << name;

            /*wcout << s << "found. quering for services\n";

            //Initialise quering the device services
            WSAQUERYSET queryset2;
            memset(&queryset2, 0, sizeof(queryset2));
            queryset2.dwSize = sizeof(queryset2);
            queryset2.dwNameSpace = NS_BTH;
            queryset2.dwNumberOfCsAddrs = 0;
            CSADDR_INFO * addr = (CSADDR_INFO *)pResults->lpcsaBuffer;
            WCHAR addressAsString[1000];
            DWORD addressSize = sizeof(addressAsString);
            WSAAddressToString(addr->RemoteAddr.lpSockaddr,addr->RemoteAddr.iSockaddrLength,NULL,addressAsString, &addressSize);
            queryset2.lpszContext = addressAsString;
            GUID protocol = L2CAP_PROTOCOL_UUID;
            queryset2.lpServiceClassId = &protocol;

            HANDLE hLookup2;
            if (WSALookupServiceBegin(&queryset2, LUP_FLUSHCACHE |LUP_RETURN_NAME |LUP_RETURN_TYPE| LUP_RETURN_BLOB | LUP_RETURN_COMMENT, &hLookup2) != 0)
            {
                qDebug() << "Fail2 : " << getLatestError();
                return;
            }*/
        }
    } while(result == 0);

}

bool BluetoothProxyWinsock::isBluetoothAvailable() const
{
   SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

   const bool canUseBluetooth = (s != INVALID_SOCKET);

   closesocket(s);

   return canUseBluetooth;
}

bool BluetoothProxyWinsock::isConnected() const
{
    return m_listenerThread->isRunning();
}

#endif
