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

/**
 * @brief The application's main class.
 *
 * This class represents the main window. It builds everything else, connects signals to slots, and manages the tabs.
 */
class Magiks: public QWidget
{
    Q_OBJECT

    public:
        /**
         * @brief Constructor
         * @param parent
         */
        explicit Magiks(QWidget *parent = nullptr);

    private:
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
