#include "bluetoothproxyqt5.h"


//#include <QBluetoothAddress>
#include <QBluetoothDeviceDiscoveryAgent>
//#include <QBluetoothServiceInfo>

#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>

BluetoothProxyQt5::BluetoothProxyQt5(QObject *parent): BluetoothProxy(parent)
{
    //setUUID("B62C4E8D-62CC-404b-BBBF-BF3E3BBB1374");

    //STM32 bluetooth adapter
    setUUID("00001101-0000-1000-8000-00805F9B34FB");

    m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent();

    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothProxyQt5::on_deviceDiscovered);

    connect(m_socket, &QBluetoothSocket::connected, this, &BluetoothProxyQt5::on_connected);
    connect(m_socket, &QBluetoothSocket::disconnected, this, &BluetoothProxyQt5::on_disconnected);
    connect(m_socket, &QBluetoothSocket::readyRead, this, &BluetoothProxyQt5::readData);
}

void BluetoothProxyQt5::connectToHost(const QString& address)
{
    disconnect();

    if(m_discoveryAgent->isActive())
        m_discoveryAgent->stop();

    m_socket->connectToService(QBluetoothAddress(address), QBluetoothUuid(getUUID()), QIODevice::ReadWrite);
}

void BluetoothProxyQt5::disconnect()
{
    m_socket->close();
}

void BluetoothProxyQt5::on_connected()
{
    emit connected();
}

void BluetoothProxyQt5::on_disconnected()
{
    emit disconnected();
}


QString BluetoothProxyQt5::remoteAddress() const
{
    return isConnected()?m_socket->peerAddress().toString():QString();
}


void BluetoothProxyQt5::readData()
{
    qDebug() << "Got milk";
    m_buffer.append(m_socket->readAll());
    processData(m_buffer);
}

void BluetoothProxyQt5::sendData(KrabiPacket& data)
{
    if(!isConnected())
        return;

    QByteArray binData = data.dataByteArray();
    binData.append(0x0D);
    binData.append(0x0A);

    qDebug() << "Sending milk";

    m_socket->write(binData);
}

void BluetoothProxyQt5::setAdapter(const QString& address)
{
    if(m_localAdapter)
    {
        disconnect();
        m_localAdapter->deleteLater();
    }

    m_localAdapter = new QBluetoothLocalDevice(QBluetoothAddress(address), this);
}

QString BluetoothProxyQt5::getAdapterAddress()
{
    return m_localAdapter->address().toString();
}

QStringList BluetoothProxyQt5::getAllLocalAdapters()
{
    QStringList localDevicesNames;

    auto l = QBluetoothLocalDevice::allDevices();

    for(auto d: l)
        localDevicesNames << d.name();

    return localDevicesNames;
}

void BluetoothProxyQt5::scanRemoteDevices()
{
    qDebug() << "Scanning...";
    m_discoveryAgent->start();
}

void BluetoothProxyQt5::on_deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    emit deviceDiscovered(info.name(), info.address().toString());
}

bool BluetoothProxyQt5::isBluetoothAvailable() const
{
    return !(QBluetoothLocalDevice::allDevices().isEmpty());
}

bool BluetoothProxyQt5::isConnected() const
{
    return (m_socket->state() == QBluetoothSocket::ConnectedState);
}
