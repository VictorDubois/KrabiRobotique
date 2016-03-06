#ifndef BLUETOOTHPROXYWINSOCK_H
#define BLUETOOTHPROXYWINSOCK_H

#ifdef BLUETOOTH_USING_WINSOCK

#include "bluetoothproxy.h"

#include <QThread>
#include <QMutex>
#include <QQueue>

#include <winsock2.h>
#include <ws2bth.h>

class BluetoothProxyWinsock : public BluetoothProxy
{
    Q_OBJECT

    private:
       class WorkerThread: public QThread
       {
           public:
               WorkerThread(BluetoothProxyWinsock* overseer);

               void softKill();
               void sendPacket(KrabiPacket packet);

           private:
               void run();

               bool m_running;
               QMutex m_runningMutex;

               QQueue<KrabiPacket> m_packetQueue;
               QMutex m_packetQueueMutex;

               QByteArray m_rcvBuffer;

               void receiveAll();
               void sendAll();

               BluetoothProxyWinsock* m_overseer;

       };

       friend class WorkerThread;

    public:
        BluetoothProxyWinsock(QObject* parent = 0);
        ~BluetoothProxyWinsock();

        virtual void connectToHost(const QString& address);
        virtual void disconnect();

        virtual void setAdapter(const QString& address = QString());
        virtual QString getAdapterAddress();

        virtual QStringList getAllLocalAdapters();

        void sendData(KrabiPacket& data);

        virtual void scanRemoteDevices();

        bool isBluetoothAvailable() const;

        virtual bool isConnected() const;

        virtual QString remoteAddress() const;

    protected:

       SOCKET m_socket;
       QMutex m_socketMutex;

    private:
       WorkerThread* m_listenerThread;

       QString m_remoteAddress;
};

#endif

#endif // BLUETOOTHPROXYWINSOCK_H
