#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <QObject>
#include <QPointF>

#include "krabipacket.h"

/**
 * @brief This class sole purpose is to process KrabiPacket structures into data usable by the rest of the application
 */
class PacketProcessor: public QObject
{
    Q_OBJECT
    public:
        /**
         * @brief Constructor.
         * @param parent
         */
        PacketProcessor(QObject* parent = nullptr);

        /**
         * @brief Process a KrabiPacket
         *
         * This method will emit all the signals relevant to the data read from the packet.
         * @param packet The packet to be processed
         */
        void processData(KrabiPacket packet);

    signals:

        /**
         * @brief Signal emitted to request a data reset
         *
         * It is typically emitted to reset the graphs
         */
        void reseted();

        /**
         * @brief Signal emitted when odometry settings has been received
         * @param wheelSize The robot's wheels' size
         * @param interAxis The inter-axis value (between the two rotary encoders' wheels)
         */
        void odometrySettingsReceived(float wheelSize, float interAxis);

        /**
         * @brief Signal emitted when angular PID values have been received
         *
         * Along with the linear PID values, they are paramount to the robot's servo-control.
         * Those control the angular response from the robot.
         * @param p Proportionnal factor
         * @param i Integral factor
         * @param d Derivative factor
         * @see linearPIDSettingsReceived
         */
        void angularPIDSettingsReceived(float p, float i, float d);

        /**
         * @brief Signal emitted when linear PID values have been received
         *
         * Along with the angular PID values, they are paramount to the robot's servo-control.
         * Those control the linear response from the robot.
         * @param p Proportionnal factor
         * @param i Integral factor
         * @param d Derivative factor
         * @see angularPIDSettingsReceived
         */
        void linearPIDSettingsReceived(float p, float i, float d);

        /**
         * @brief Signal emitted when a log has been received
         * @param log The log itself
         * @param isDebug True is the log is considered as 'debug' info
         */
        void logReceived(QString log, bool isDebug);

        /**
         * @brief Signal emitted when a variable watch has finished syncing.
         * @param packet The packet containing the watch data
         */
        void watchesSyncFinished(KrabiPacket packet);

        /**
         * @brief Signal emitted when plot data has been received
         * @param idx The plot index
         * @param data The data to plot
         */
        void plotDataReceived(int idx, float data);

        /**
         * @brief Signal emitted when the robot's position has been received
         * @param position The robot's position, in milimeters
         */
        void robotPositionReceived(QPointF position);

        /**
         * @brief Signal emitted when the robot's angle has been received
         * @param angle The robot's angle, in degrees
         */
        void robotAngleReceived(float angle);

    private:
        /**
         * @brief Process the WATCH commands from a PacketProcessor
         *
         * This method only exists to make processData easier to read.
         * @param packet The packet to be processed
         */
        void watch(KrabiPacket packet);
};

#endif // PACKETPROCESSOR_H
