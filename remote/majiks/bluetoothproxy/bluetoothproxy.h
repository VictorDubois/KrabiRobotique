#ifndef BLUETOOTHPROXY_H
#define BLUETOOTHPROXY_H

#include "serialproxy/abstractserialproxy.h"

#include <QString>

/**
 * @brief An abstract class providing an interface for plateform-specific Bluetooth serial connections
 */
class BluetoothProxy: public AbstractSerialProxy
{
    Q_OBJECT
    public:
        /**
         * @brief Constructor
         * @param parent
         */
        explicit BluetoothProxy(QObject *parent = 0);

        /**
         * @brief Connect to a remote Bluetooth host.
         *
         * Tries to establish a connection to the remote host, using the UUID given by setUUID.
         * @param address The address of the host
         * @see setUUID connected
         */
        virtual void connectToHost(const QString& address) = 0;

        /**
         * @brief Disconnect from the remote host
         */
        virtual void disconnect()                                       = 0;

        /**
         * @brief Set the local Bluetooth adapter to use
         *
         * Set the local Bluetooth adapter to use for upcoming connections.
         * Note it will reset the connection.
         * @param address The address of the adapter to use
         */
        virtual void setAdapter(const QString& address)                 = 0;

        /**
         * @return The address of the current Bluetooth adapter, or an empty QString
         */
        virtual QString getAdapterAddress()                             = 0;

        /**
         * @brief Returns a list of the local Bluetooth adapters
         * @return A list of the local adapters
         */
        virtual QStringList getAllLocalAdapters()                       = 0;

        /**
         * @brief Initiate a scan of remote Bluetooth devices.
         *
         * This function starts a scan of remote Bluetooth devices. For each and every
         * device discovered, a deviceDiscovered() signal will be emitted.
         * Note that on some plateform, cached devices may be returned, even though
         * they are not in range.
         *
         * @see deviceDiscovered
         */
        virtual void scanRemoteDevices()                                = 0;

        /**
         * @return True is Bluetooth is available on the machine
         */
        virtual bool isBluetoothAvailable() const                       = 0;

        /**
         * @return True is a connection has been established, false otherwise.
         */
        virtual bool isConnected() const                                = 0;

        /**
         * @return The current remote MAC address or an empty QString
         */
        virtual QString remoteAddress() const                           = 0;

        /**
         * @brief Set the UUID
         *
         * Bluetooth UUIDs are a 128-bits 'unique' identifier used to identify a Bluetooth service.
         * While the Bluetooth architecture may be used in a way akin to TCP/UDP (a server, multiple clients, connection through
         * a combination of an address and a port), it is not flexible in any way and inadequate for anything that is not local
         * testing. As such, the service provided by the server (and therefore the protocol used over Bluetooth) has to be
         * identified in some way. The Bluetooth stack will then take care of the port assignation.
         * This means that for a Bluetooth client to connect to a Bluetooth server, the both of them must have the same UUID.
         * See <a href="https://en.wikipedia.org/wiki/Universally_unique_identifier#Version_5_.28SHA-1_hash_.26_namespace.29">here</a>
         * and <a href="https://en.wikipedia.org/wiki/Bluetooth#SDP">here</a> for more informations.
         * @param UUID The UUID formated as 'XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXX', X being an hexadecimal symbol
         */
        void setUUID(const QString& UUID);

        /**
         * @brief Returns the current UUID (see setUUID for more details)
         * @return The UUID formated as 'XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXX' or an empty QString
         * @see setUUID
         */
        QString getUUID() const;

    signals:
        /**
         * @brief Signal emitted when a remote Bluetooth device is discovered.
         *
         * This signal is emitted every time a remote Bluetooth device is discovered.
         * If N devices are discovered, then it will be call N times, sequentially.
         * Note that on some plateforms, those devices may be cached by the OS, but not actually in range.
         * @param name The name of the remote device
         * @param address The MAC address of the remote device
         */
        void deviceDiscovered(QString name, QString address);

    private:
        QString m_UUID;
        QString m_remoteAddress;

};

#endif // BLUETOOTHPROXY_H
