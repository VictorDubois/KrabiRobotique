#ifndef BLUETOOTHPROXYQT5_H
#define BLUETOOTHPROXYQT5_H

#include "bluetoothproxy.h"

#include <QByteArray>

class QBluetoothLocalDevice;
class QBluetoothSocket;
class QBluetoothDeviceDiscoveryAgent;
class QBluetoothDeviceInfo;

class BluetoothProxyQt5 : public BluetoothProxy
{
    Q_OBJECT
    public:
        BluetoothProxyQt5(QObject* parent = 0);

        virtual void connectToHost(const QString& address);
        virtual void disconnect();

        virtual void setAdapter(const QString& address = QString());
        virtual QString getAdapterAddress();

        virtual QStringList getAllLocalAdapters();

        void sendData(KrabiPacket& data);

        virtual void scanRemoteDevices();

        virtual bool isBluetoothAvailable() const;

        virtual bool isConnected() const;

        QString remoteAddress() const;

    signals:

        void connected();
        void disconnected();

        void dataReceived(KrabiPacket data);

    protected:

        QBluetoothLocalDevice* m_localAdapter;
        QBluetoothSocket* m_socket;
        QBluetoothDeviceDiscoveryAgent* m_discoveryAgent;

    private:

        void on_connected();
        void on_disconnected();
        void on_deviceDiscovered(const QBluetoothDeviceInfo &info);

        void readData();

        QByteArray m_buffer;

};

#endif // BLUETOOTHPROXYQT5_H
