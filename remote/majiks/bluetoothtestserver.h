#ifndef BLUETOOTHTESTSERVER_H
#define BLUETOOTHTESTSERVER_H

#include <QObject>

#include <QByteArray>

class QBluetoothServer;
class QBluetoothSocket;

class BluetoothTestServer: public QObject
{
    public:
        BluetoothTestServer(QObject* parent = 0);

    signals:

    private:

        void receiveData(QBluetoothSocket* client);
        void clientDisconnected(QBluetoothSocket* client);
        void clientConnected();
        int processData(QByteArray& data);

        QBluetoothServer* m_server;
        QList<QBluetoothSocket*> m_clients;

        QByteArray m_buffer;

};

#endif // BLUETOOTHTESTSERVER_H
