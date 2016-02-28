#ifndef BLUETOOTHPROXY_H
#define BLUETOOTHPROXY_H

#include <QObject>
#include <QString>

#include "krabipacket.h"

class BluetoothProxy: public QObject
{
    Q_OBJECT
    public:
        explicit BluetoothProxy(QObject *parent = 0);

        virtual void connectToHost(const QString& address  = QString()) = 0;
        virtual void disconnect()                                       = 0;

        virtual void setAdapter(const QString& address)                 = 0;
        virtual QString getAdapterAddress()                             = 0;

        virtual QStringList getAllLocalAdapters()                       = 0;

        virtual void sendData(KrabiPacket& data)                        = 0;

        virtual void scanRemoteDevices()                                = 0;

        virtual bool isBluetoothAvailable() const                       = 0;

        virtual bool isConnected() const                                = 0;

        virtual QString remoteAddress() const                           = 0;

        void setUUID(const QString& UUID);
        QString getUUID() const;

    signals:

        void deviceDiscovered(const QString& name, const QString& address);

        void connected();
        void disconnected();

        void dataReceived(KrabiPacket data);

    protected:

        int processData(QByteArray&);

    private:

        QString m_UUID;
        QString m_remoteAddress;

};

#endif // BLUETOOTHPROXY_H
