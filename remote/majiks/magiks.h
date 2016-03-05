#ifndef MAGIKS_H
#define MAGIKS_H

#include <QWidget>

class BluetoothProxy;
class PacketProcessor;
class OdometryWindow;
class WatchWindow;
class AsservWindow;
class BluetoothManagementWidget;
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

        BluetoothProxy* m_bluetoothProxy;

        PacketProcessor*            m_packetProcessor;
        OdometryWindow*             m_odometry;
        WatchWindow*                m_watches;
        AsservWindow*               m_asserv;
        BluetoothManagementWidget*  m_bluetoothManagement;
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
