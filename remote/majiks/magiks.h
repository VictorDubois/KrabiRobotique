#ifndef MAGIKS_H
#define MAGIKS_H

//#define BLUETOOTH_SERVER_MODE

#include <QWidget>

class AbstractSerialProxy;
class PacketProcessor;
class OdometryWindow;
class WatchWindow;
class AsservWindow;
class SerialManagementWidget;
class LoggerWidget;
class PlotWidget;
class TableWidget;
class RemoteWidget;
class MovementSettingsWidget;

class QTabWidget;

class Magiks: public QWidget
{
    Q_OBJECT

    public:
        explicit Magiks(QWidget *parent = nullptr);

    private:
        void connected();
        void disconnected();

        AbstractSerialProxy* m_serialProxy;

        PacketProcessor*            m_packetProcessor;
        OdometryWindow*             m_odometry;
        WatchWindow*                m_watches;
        AsservWindow*               m_asserv;
        SerialManagementWidget*     m_serialManagement;
        LoggerWidget*               m_logger;
        PlotWidget*                 m_plots;
        TableWidget*                m_table;
        RemoteWidget*               m_remote;
        MovementSettingsWidget*     m_remoteSettings;

        QTabWidget*  m_tabs;
        QTabWidget*  m_remoteControlTab;
        QTabWidget*  m_robotSettingsTab;

};

#endif // MAGIKS_H
