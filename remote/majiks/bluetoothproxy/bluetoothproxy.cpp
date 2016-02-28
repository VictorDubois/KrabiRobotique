#include "bluetoothproxy.h"

#include <QDebug>

BluetoothProxy::BluetoothProxy(QObject *parent) : QObject(parent)
{

}

QString BluetoothProxy::getUUID() const
{
    return m_UUID;
}

void BluetoothProxy::setUUID(const QString& UUID)
{
    m_UUID = UUID;
}

int BluetoothProxy::processData(QByteArray& data)
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
                emit dataReceived(packet);
                qDebug() << "Received valid packet";
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
