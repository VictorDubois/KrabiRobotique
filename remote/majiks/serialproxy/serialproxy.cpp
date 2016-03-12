#include "serialproxy.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>

SerialProxy::SerialProxy(qint32 baudrate, QObject *parent): AbstractSerialProxy(parent)
{
    m_serialPort = new QSerialPort(this);

    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialProxy::readData);
    setBaudrate(baudrate);
}

#ifdef SERIAL_ENABLED
bool SerialProxy::setBaudrate(qint32 baudrate)
{
    return !m_serialPort->setBaudRate(baudrate);
}

qint32 SerialProxy::getBaudrate() const
{
    return m_serialPort->baudRate();
}

QString SerialProxy::getPortName() const
{
    if(!isOpen())
        return QString();

    return m_serialPort->portName();
}

bool SerialProxy::open(QString port)
{
    close();

    if(port.isEmpty())
    {
        QList<QSerialPortInfo> l = QSerialPortInfo::availablePorts();

        if(l.isEmpty())
        {
            qDebug() << "Error: no port specified and no default port found. Aborting...";
            return true;
        }
        port = l[0].portName();
    }

    m_serialPort->setPortName(port);

    if(!(m_serialPort->open(QIODevice::ReadWrite)))
    {
        qDebug() << "Error: couldn't open serial port " << port;
        return true;
    }

    emit connected();

    return false;
}

bool SerialProxy::isOpen() const
{
    return m_serialPort->isOpen();
}

void SerialProxy::close()
{
    if(isOpen())
    {
        m_serialPort->close();
        emit disconnected();
    }
}

void SerialProxy::readData()
{
    m_buffer.append(m_serialPort->readAll());
    processData(m_buffer);
}

void SerialProxy::sendData(KrabiPacket& data)
{
    if(!isOpen())
        return;

    QByteArray binData = data.dataByteArray();
    binData.append(0x0D);
    binData.append(0x0A);

    m_serialPort->write(binData);
}

#endif
