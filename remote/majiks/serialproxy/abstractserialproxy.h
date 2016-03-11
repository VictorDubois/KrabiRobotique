#ifndef ABSTRACTSERIALPROXY_H
#define ABSTRACTSERIALPROXY_H

#include <QObject>
#include "krabipacket.h"

/**
 * @brief An abstract class providing an interface for serial communications
 */
class AbstractSerialProxy: public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param parent
         */
        AbstractSerialProxy(QObject* parent = nullptr);

        /**
         * @brief Send data through the serial link
         *
         * Send a packet through the serial link.
         * Note a connection has to be established beforehand. Otherwise,
         * the packet will be discarded.
         * @param data The data to be sent
         * @see dataReceived
         */
        virtual void sendData(KrabiPacket& data)                        = 0;


    signals:
        /**
         * @brief Signal emitted when data has been received
         *
         * @param data The received data
         */
        void dataReceived(KrabiPacket data);

        /**
         * @brief Signal emitted when a connection is successfuly established.
         * @see connectToHost
         */
        void connected();

        /**
         * @brief Signal emitted when the connection is interupted.
         * @see disconnect
         */
        void disconnected();

    protected:
        /**
         * @brief Process incomming data from binary format to Krabi packets
         *
         * This function extracts as many KrabiPacket structures from a byte array as possible.
         * For every processed packet, a dataReceived() signal will be emitted.
         * @param data The byte array to be processed
         * @return The numbers of packets processed
         * @see dataReceived
         */
        int processData(QByteArray& data);

    private:

};

#endif // ABSTRACTSERIALPROXY_H
