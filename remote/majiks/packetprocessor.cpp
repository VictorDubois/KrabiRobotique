#include "packetprocessor.h"

#include "../../stm32/include/hardware/krabipacket.h"
#include "../../stm32/include/positionPlusAngle.h"

#include "subwindows/plotwidget.h"
#include "timemaster.h"

#include <QDebug>

PacketProcessor::PacketProcessor(QObject *parent): QObject(parent) {}


void PacketProcessor::processData(KrabiPacket packet)
{
    switch(packet.id())
    {
        case KrabiPacket::LOG_NORMAL:
            emit logReceived(packet.getString(), false);
            break;
        case KrabiPacket::LOG_DEBUG:
            emit logReceived(packet.getString(), true);
            break;
        case KrabiPacket::WATCH_VARIABLE:
            watch(packet);
            break;
        case KrabiPacket::ASSERV_RESULT:
        {
            uint32_t time       = packet.get<uint32_t>();
            float vitesseLin    = packet.get<float>();
            float vitesseLinE   = packet.get<float>();
            float linearDuty    = packet.get<float>();
            float vitesseAng    = packet.get<float>();
            float vitesseAngE   = packet.get<float>();
            float angularDuty   = packet.get<float>();

            qDebug() << "Krabi Results" << time;

            if (time == 0)
                emit reseted();

            emit plotDataReceived(PlotWidget::LINEAR_SPEED, vitesseLin);
            emit plotDataReceived(PlotWidget::LINEAR_TARGET, vitesseLinE);
            emit plotDataReceived(PlotWidget::LINEAR_DUTY, linearDuty);
            emit plotDataReceived(PlotWidget::ANGULAR_SPEED, vitesseAng);
            emit plotDataReceived(PlotWidget::ANGULAR_TARGET, vitesseAngE);
            emit plotDataReceived(PlotWidget::ANGULAR_DUTY, angularDuty);

            break;
        }
        case KrabiPacket::TIME_SYNC:
        {
            int t = packet.get<uint16_t>();

            int diff = t - TimeMaster::getInstance()->getCurrentTime();

            if (abs(diff) > 25)
                qDebug() << "Timer sync error (" << diff << " ms)";

            TimeMaster::getInstance()->delta(t);
            break;
        }
        default:
            qDebug() << "Uncaught packet : " << packet.id() << packet.length();
            break;
    }
}


void PacketProcessor::watch(KrabiPacket packet)
{
    uint16_t type = packet.get<uint16_t>();

    switch(type)
    {
        case KrabiPacket::W_POSITION:
        {
            float x = packet.get<float>();
            float y = packet.get<float>();
            float ang = packet.get<float>();

            emit robotPositionReceived(QPointF(x, y));
            emit robotAngleReceived(ang);
            break;
        }
        case KrabiPacket::W_SPEED:
        {
            float l = packet.get<float>();
            float a = packet.get<float>();

            emit plotDataReceived(PlotWidget::LINEAR_SPEED, l);
            emit plotDataReceived(PlotWidget::ANGULAR_SPEED, a*100.f);

            break;
        }
        case KrabiPacket::W_SPEED_TARGET:
        {
            float l = packet.get<float>();
            float a = packet.get<float>();

            emit plotDataReceived(PlotWidget::LINEAR_TARGET, l);
            emit plotDataReceived(PlotWidget::ANGULAR_TARGET, a*100.f);

            break;
        }
        case KrabiPacket::W_PID_ANG:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();

            emit angularPIDSettingsReceived(p, i, d);
            break;
        }
        case KrabiPacket::W_PID_LIN:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();

            emit linearPIDSettingsReceived(p, i, d);
            break;
        }
        case KrabiPacket::W_ODOMETRIE:
        {
            float wheelsize = packet.get<float>();
            float interaxis = packet.get<float>();

            emit odometrySettingsReceived(wheelsize, interaxis);
            break;
        }
        case KrabiPacket::W_WATCHES:
            emit watchesSyncFinished(packet);
            break;
        case KrabiPacket::W_SHARPS:
            //DebugWindow::getInstance()->getSharpWindow()->syncFinished(packet);
            qDebug() << "SHARPS watches not implemented";
            break;
        default:
            qDebug() << "Uncaught watch: " << type;
            break;
    }
}
