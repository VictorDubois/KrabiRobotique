#include "bluetoothproxywinsock.h"

#ifdef BLUETOOTH_USING_WINSOCK
#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>

#include <QDebug>
#include <QMutexLocker>

#include <memory>
#include <string>
#include <vector>

// {B62C4E8D-62CC-404b-BBBF-BF3E3BBB1374}
DEFINE_GUID(g_guidServiceClass, 0xb62c4e8d, 0x62cc, 0x404b, 0xbb, 0xbf, 0xbf, 0x3e, 0x3b, 0xbb, 0x13, 0x74);
QString getLatestError(int errorCode = 0)
{
    static TCHAR errmsg[512];
    int er = ((errorCode == 0) ? WSAGetLastError() : errorCode);

    if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, er, 0, errmsg, 511, NULL))
    {
    /* if we fail, call ourself to find out why and return that error */
        qDebug() << "Error reporting... got an error.";
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

    //connectToHost("00:1A:7D:DA:71:05");

}

BluetoothProxyWinsock::WorkerThread::WorkerThread(BluetoothProxyWinsock* overseer): QThread(overseer),m_running(false),m_overseer(overseer) {}

BluetoothProxyWinsock::~BluetoothProxyWinsock()
{
    WSACleanup();
    qDebug() << "Winsock2 cleaned up";
}


bool CharToDigit(char c, uint8_t* digit) {
    if (c >= '0' && c <= '9') {
      *digit = c - '0';
    } else if (c >= 'a' && c < 'a' + 16 - 10) {
      *digit = c - 'a' + 10;
    } else if (c >= 'A' && c < 'A' + 16 - 10) {
      *digit = c - 'A' + 10;
    } else {
      return false;
    }
    return true;
}

bool HexStringToBytes(const std::string& input, std::vector<uint8_t>* output)
{
  //DCHECK_EQ(output->size(), 0u);
  size_t count = input.size();
  if (count == 0 || (count % 2) != 0)
    return false;
  for (uintptr_t i = 0; i < count / 2; ++i) {
    uint8_t msb = 0;  // most significant 4 bits
    uint8_t lsb = 0;  // least significant 4 bits
    if (!CharToDigit(input[i * 2], &msb) ||
        !CharToDigit(input[i * 2 + 1], &lsb))
      return false;
    output->push_back((msb << 4) | lsb);
  }
  return true;
}

BTH_ADDR ConvertToBthAddr(const QString& add)
{
  std::string address = add.toStdString();
  BTH_ADDR bth_addr = 0;
  std::string numbers_only;
  for (int i = 0; i < 6; ++i) {
    numbers_only += address.substr(i * 3, 2);
  }

  std::vector<uint8_t> address_bytes;
  HexStringToBytes(numbers_only, &address_bytes);
  int byte_position = 0;
  for (std::vector<uint8_t>::reverse_iterator iter = address_bytes.rbegin();
       iter != address_bytes.rend(); ++iter) {
    bth_addr += *iter * pow(256.0, byte_position);
    byte_position++;
  }
  return bth_addr;
}

void BluetoothProxyWinsock::connectToHost(const QString& address)
{
    // Will soft-kill the listener thread
    disconnect();

    SOCKADDR_BTH addressStruct = {0};

    //WSAStringToAddress((LPTSTR)(address.toStdString().c_str()), AF_BTH, NULL, reinterpret_cast<sockaddr*>(&addressStruct), (LPINT)sizeof(SOCKADDR_BTH));

    qDebug() << "Address: " << addressStruct.btAddr;

    addressStruct.btAddr = ConvertToBthAddr(address);

    qDebug() << "Address: " << addressStruct.btAddr;

    addressStruct.addressFamily     = AF_BTH;
    addressStruct.serviceClassId    = g_guidServiceClass;
    addressStruct.port              = 0;

    // Will wait for the listener thread to stop
    QMutexLocker lock(&m_socketMutex);

    m_socket = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
    if(m_socket == INVALID_SOCKET)
    {
        qDebug() << "Socket PoS init failed";
        return;
    }

    qDebug() << "Socket init OK";

    if(::connect(m_socket, (struct sockaddr*)&addressStruct, sizeof(SOCKADDR_BTH)) == SOCKET_ERROR)
    {
        qDebug() << "Socket PoS couldn't connect to " << address;
        qDebug() << "Error: " << getLatestError();
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
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
            QString name = QString::fromWCharArray(pResults->lpszServiceInstanceName);

            WCHAR wAddress[100];
            DWORD wSize = sizeof(wAddress);
            WSAAddressToString(pResults->lpcsaBuffer->RemoteAddr.lpSockaddr,pResults->lpcsaBuffer->RemoteAddr.iSockaddrLength,NULL, wAddress, &wSize);
            QString address = QString::fromWCharArray(wAddress);

            emit deviceDiscovered(name, address.mid(1, address.size()-2));
        }
    } while(result == 0);

    WSALookupServiceEnd(&hLookup);

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
