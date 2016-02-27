#include "packetprocessor.h"

#include "subwindows/odometriewindow.h"
#include "subwindows/asservwindow.h"
#include "subwindows/watchwindow.h"
#include "subwindows/loggerwidget.h"

#include "../../stm32/include/hardware/krabipacket.h"
#include "../../stm32/include/positionPlusAngle.h"

#include "timemaster.h"

#include <QDebug>

PacketProcessor::PacketProcessor(OdometrieWindow *odometrie, GraphWindow *graphs, WatchWindow *watches, AsservWindow *asserv, LoggerWidget* logger)
{
    m_odometrie     = odometrie;
    m_graphs        = graphs;
    m_watches       = watches;
    m_asserv        = asserv;
    m_logger        = logger;
}


void PacketProcessor::processData(KrabiPacket packet)
{
    switch(packet.id())
    {
        case KrabiPacket::LOG_NORMAL:
            m_logger->log(packet.getString());
            break;
        case KrabiPacket::LOG_DEBUG:
            m_logger->log(packet.getString(), true);
            break;
        case KrabiPacket::WATCH_VARIABLE:
            watch(packet);
            break;
        case KrabiPacket::ASSERV_RESULT:
        {
            uint32_t time       = packet.get<uint32_t>();
            /*float vitesseLin    = packet.get<float>();
            float vitesseLinE   = packet.get<float>();
            float linearDuty    = packet.get<float>();
            float vitesseAng    = packet.get<float>();
            float vitesseAngE   = packet.get<float>();
            float angularDuty   = packet.get<float>();*/

            qDebug() << "Krabi Results" << time;

            if (time == 0)
                emit reseted();

            if(m_asserv->graphLinear())
            {
                /*DebugWindow::getInstance()->plot(0, "Linear Speed", vitesseLin, time);
                DebugWindow::getInstance()->plot(1, "Linear Target", vitesseLinE, time);*/
            }
            if (m_asserv->graphAngular())
            {
                /*DebugWindow::getInstance()->plot(2, "Angular Speed", vitesseAng, time);
                DebugWindow::getInstance()->plot(3, "Angular Target", vitesseAngE, time);*/
            }
            if (m_asserv->graphDuty())
            {
                /*DebugWindow::getInstance()->plot(6, "Linear Duty", linearDuty, time);
                DebugWindow::getInstance()->plot(7, "Angular Duty", angularDuty, time);*/
            }
            break;
        }
        case KrabiPacket::TIME_SYNC:
        {
            int t = packet.get<uint16_t>();

            int diff = t - TimeMaster::getInstance()->getCurrentTime();

            if (abs(diff) > 25)
            {
                qDebug() << "Timer sync error (" << diff << "ms)";
            }

            /*if (diff < -1500)
            {
                DebugWindow::getInstance()->clearPlots();
                qDebug() << "Timer restart";
            }*/

            TimeMaster::getInstance()->delta(t);
            //qDebug() << "Timer" << t << t / 1000 << t % 1000;
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
           /* float x = packet.get<float>();
            float y = packet.get<float>();
            float ang = packet.get<float>();

            PositionPlusAngle newPos = PositionPlusAngle(Position(x, y), ang);*/

            //getMainRobot()->setPos(newPos);
            /*if (previousPosition)
                DebugWindow::getInstance()->getOdometrieWindow()->addRelative(newPos.position - previousPos.position, newPos.angle - previousPos.angle);*/
           /* previousPos = newPos;
            previousPosition = true;*/
            break;
        }
        case KrabiPacket::W_SPEED:
        {
            /*float l = packet.get<float>();
            float a = packet.get<float>();
            DebugWindow::getInstance()->plot(0, "Linear Speed", l);
            DebugWindow::getInstance()->plot(1, "Angular Speed", a * 100.);*/
            break;
        }
        case KrabiPacket::W_SPEED_TARGET:
        {
            /*float l = packet.get<float>();
            float a = packet.get<float>();
            DebugWindow::getInstance()->plot(2, "Linear Target", l);
            DebugWindow::getInstance()->plot(3, "Angular Target", a * 100.);*/
            break;
        }
        case KrabiPacket::W_PID_ANG:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();

            m_asserv->settingsReceivedAngular(p, i, d);
            break;
        }
        case KrabiPacket::W_PID_LIN:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();

            m_asserv->settingsReceivedLinear(p, i, d);
            break;
        }
        case KrabiPacket::W_ODOMETRIE:
        {
            float wheelsize = packet.get<float>();
            float interaxis = packet.get<float>();

            m_odometrie->settingsReceived(wheelsize, interaxis);
            break;
        }
        case KrabiPacket::W_WATCHES:
            m_watches->syncFinished(packet);
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
