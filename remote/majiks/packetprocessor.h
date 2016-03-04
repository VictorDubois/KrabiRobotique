#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <QObject>
#include <QPointF>

#include "krabipacket.h"

class PacketProcessor: public QObject
{
    Q_OBJECT
    public:
        PacketProcessor(QObject* parent);

        void processData(KrabiPacket packet);

    signals:

        void reseted();
        void odometrySettingsReceived(float wheelSize, float interAxis);
        void angularPIDSettingsReceived(float p, float i, float d);
        void linearPIDSettingsReceived(float p, float i, float d);
        void logReceived(QString log, bool isDebug);
        void watchesSyncFinished(KrabiPacket packet);
        void plotDataReceived(int idx, float data);
        void robotPositionReceived(QPointF position);
        void robotAngleReceived(float angle);

    private:
        void watch(KrabiPacket packet);
        void resetTimer();
};

#endif // PACKETPROCESSOR_H
