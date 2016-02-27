#ifndef PACKETPROCESSOR_H
#define PACKETPROCESSOR_H

#include <QObject>
#include <QTime>

//#include "../../stm32/include/hardware/krabipacket.h"

class OdometrieWindow;
class GraphWindow;
class WatchWindow;
class AsservWindow;
class LoggerWidget;
class KrabiPacket;

class PacketProcessor: public QObject
{
    Q_OBJECT
    public:
        PacketProcessor(OdometrieWindow* odometrie, GraphWindow* graphs, WatchWindow* watches, AsservWindow* asserv, LoggerWidget* logger);

        void processData(KrabiPacket packet);

    signals:

        void reseted();

    private:
        void watch(KrabiPacket packet);
        void resetTimer();

        OdometrieWindow*    m_odometrie;
        GraphWindow*        m_graphs;
        WatchWindow*        m_watches;
        AsservWindow*       m_asserv;
        LoggerWidget*       m_logger;
};

#endif // PACKETPROCESSOR_H
