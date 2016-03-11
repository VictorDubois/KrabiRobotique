#ifndef SERIALPROXY_H
#define SERIALPROXY_H

#include "abstractserialproxy.h"

class QSerialPort;

class SerialProxy : public AbstractSerialProxy
{
    public:
        SerialProxy(qint32 baudrate = 9600, QObject* parent = nullptr);

        virtual void sendData(KrabiPacket& data);

        bool setBaudrate(qint32 baudrate);
        qint32 getBaudrate() const;

        QString getPortName() const;

        bool open(QString port);
        void close();

        bool isOpen() const;

    protected:
        void readData();

    private:

        QSerialPort* m_serialPort;
        QByteArray m_buffer;
};

#endif // SERIALPROXY_H
