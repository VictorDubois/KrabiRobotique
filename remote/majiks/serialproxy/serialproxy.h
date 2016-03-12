#ifndef SERIALPROXY_H
#define SERIALPROXY_H

#include "abstractserialproxy.h"

class QSerialPort;

/**
 * @brief This class provides an implementation of AbstractSerialProxy as a physical serial connection (COM)
 *
 * This class provides an implementation of AbstractSerialProxy as a physical serial connection (COM).
 * Since it uses QtSerial, it should work with most plateforms.
 * Note Qt is not always compiled with QtSerial enabled (it isn't on Android). You can disable serial support entierely through majiks.pro.
 */
class SerialProxy : public AbstractSerialProxy
{
    public:
         /**
         * @brief Constructor
         * @param baudrate  The baudrate to use. It is preferable (but not mandatory) to use constants from QSerialPort::BaudRate.
         * @param parent    The parent object
         */
        SerialProxy(qint32 baudrate = 9600, QObject* parent = nullptr);

        virtual void sendData(KrabiPacket& data);

        /**
         * @brief It is preferable (but not mandatory) to use constants from QSerialPort::BaudRate.
         * @param baudrate
         * @return True if an error happened (i.e. invalid baudrate), false otherwise.
         */
        bool setBaudrate(qint32 baudrate);
        /**
         * @brief Return the baudrate
         * @return
         */
        qint32 getBaudrate() const;

        /**
         * @brief Returns the port name as a QString
         * @return The port name or an empty QString
         */
        QString getPortName() const;

        /**
         * @brief Open the serial port. Any previous connection is dropped.
         * @param The port name to use. If empty, uses any available port.
         * @return True on error, false otherwise
         * @see close isOpen
         */
        bool open(QString port = QString());
        /**
         * @brief Close the current connection.
         * @see isOpen open
         */
        void close();

        /**
         * @return True if a valid connection to a serial port exists, false otherwise.
         * @see open close
         */
        bool isOpen() const;

    protected:
        /**
         * @brief Handles the incomming data
         */
        void readData();

    private:

        QSerialPort* m_serialPort;
        QByteArray m_buffer;
};

#endif // SERIALPROXY_H
