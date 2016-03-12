#include "bluetoothproxy.h"

BluetoothProxy::BluetoothProxy(QObject *parent) : AbstractSerialProxy(parent)
{}

QString BluetoothProxy::getUUID() const
{
    return m_UUID;
}

void BluetoothProxy::setUUID(const QString& UUID)
{
    m_UUID = UUID;
}
