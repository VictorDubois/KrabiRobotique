#include "bluetoothtestserver.h"

#include <QBluetoothServer>
#include <QBluetoothSocket>
#include <QBluetoothUuid>

#include "krabipacket.h"

#include <functional>

BluetoothTestServer::BluetoothTestServer(QObject *parent): QObject(parent)
{
     m_server = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);

     connect(m_server, &QBluetoothServer::newConnection, this, &BluetoothTestServer::clientConnected);

     QBluetoothServiceInfo info = m_server->listen(QBluetoothUuid(QString("B62C4E8D-62CC-404b-BBBF-BF3E3BBB1374")));

     if(!info.isValid())
     {
         qDebug() << "Cannot setup server";
     }
     else
         qDebug() << "Server started";
}

void BluetoothTestServer::clientConnected()
{
    QBluetoothSocket *socket = m_server->nextPendingConnection();
    if (!socket)
        return;

    connect(socket, &QBluetoothSocket::readyRead, std::bind(&BluetoothTestServer::receiveData, this, socket));
    connect(socket, &QBluetoothSocket::disconnected, std::bind(&BluetoothTestServer::clientDisconnected, this, socket));

    m_clients.append(socket);

    qDebug() << "Client connected: " << socket->peerName();
}


void BluetoothTestServer::receiveData(QBluetoothSocket* client)
{
    qDebug() << "Data received!";

    m_buffer.append(client->readAll());

    processData(m_buffer);
}


int BluetoothTestServer::processData(QByteArray& data)
{
    if(data.size() < 2)
        return 0;

    int packetsProcessed = 0;

    for(int i = 0; i < data.size() -1; ++i)
    {
        if(! (data.at(i) == 0x0D && data.at(i+1) == 0x0A))
            continue;

        if (i < KRABIPACKET_MAXSIZE)
        {
            KrabiPacket packet(data.left(i));

            if (packet.isValid())
            {
                qDebug() << "Received valid packet";
                qDebug() << "Type: " << packet.id();
            }
            else
                qDebug() << "Discarding packet (invalid checksum)";
            ++packetsProcessed;
        }

        data = data.right(data.size() - (i + 2));
        i = 0;
    }

    return packetsProcessed;
}



void BluetoothTestServer::clientDisconnected(QBluetoothSocket* client)
{
    qDebug() << "Client disconnected";
    m_clients.removeAll(client);
}
