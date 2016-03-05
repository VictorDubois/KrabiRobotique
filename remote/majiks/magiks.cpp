#include "magiks.h"

#ifdef BLUETOOTH_USING_WINSOCK
#include "bluetoothproxy/bluetoothproxywinsock.h"
#else
#include "bluetoothproxy/bluetoothproxyqt5.h"
#endif

#include <QTabWidget>
#include <QVBoxLayout>
#include <QDebug>

#include "subwindows/bluetoothmanagementwidget.h"
#include "subwindows/odometrywindow.h"
#include "subwindows/asservwindow.h"
#include "subwindows/watchwindow.h"
#include "subwindows/loggerwidget.h"
#include "subwindows/plotwidget.h"
#include "subwindows/tablewidget.h"
#include "subwindows/remotewidget.h"
#include "subwindows/movementsettingswidget.h"
#include "packetprocessor.h"

#include "bluetoothtestserver.h"

Magiks::Magiks(QWidget *parent): QWidget(parent)
{
    setWindowTitle(tr("Magiks - Robot remote"));
#if 1
#ifdef BLUETOOTH_USING_WINSOCK
    m_bluetoothProxy = new BluetoothProxyWinsock(this);
#else
    m_bluetoothProxy = new BluetoothProxyQt5(this);
#endif

    m_bluetoothManagement   = new BluetoothManagementWidget(m_bluetoothProxy);
    m_odometry              = new OdometryWindow(m_bluetoothProxy);
    m_asserv                = new AsservWindow(m_bluetoothProxy);
    m_watches               = new WatchWindow(m_bluetoothProxy);
    m_logger                = new LoggerWidget();
    m_plots                 = new PlotWidget();
    m_table                 = new TableWidget(m_bluetoothProxy);
    m_remote                = new RemoteWidget(m_bluetoothProxy);
    m_remoteSettings        = new MovementSettingsWidget();

    m_packetProcessor = new PacketProcessor(this);

    connect(m_packetProcessor,  &PacketProcessor::odometrySettingsReceived,      m_odometry, &OdometryWindow::settingsReceived);
    connect(m_packetProcessor,  &PacketProcessor::robotPositionReceived,         m_odometry, &OdometryWindow::setCurrentRobotPosition);
    connect(m_packetProcessor,  &PacketProcessor::robotAngleReceived,            m_odometry, &OdometryWindow::setCurrentRobotAngle);
    connect(m_packetProcessor,  &PacketProcessor::linearPIDSettingsReceived,     m_asserv,   &AsservWindow::settingsReceivedLinear);
    connect(m_packetProcessor,  &PacketProcessor::angularPIDSettingsReceived,    m_asserv,   &AsservWindow::settingsReceivedAngular);
    connect(m_packetProcessor,  &PacketProcessor::logReceived,                   m_logger,   &LoggerWidget::log);
    connect(m_packetProcessor,  &PacketProcessor::watchesSyncFinished,           m_watches,  &WatchWindow::syncFinished);
    connect(m_packetProcessor,  &PacketProcessor::plotDataReceived,              m_plots,    &PlotWidget::addDataToPlot);
    connect(m_packetProcessor,  &PacketProcessor::reseted,                       m_plots,    &PlotWidget::clear);
    connect(m_packetProcessor,  &PacketProcessor::robotPositionReceived,         m_table,    &TableWidget::setRobotPosition);
    connect(m_packetProcessor,  &PacketProcessor::robotAngleReceived,            m_table,    &TableWidget::setRobotAngle);

    connect(m_bluetoothProxy,   &BluetoothProxy::connected,             this,               &Magiks::connected);
    connect(m_bluetoothProxy,   &BluetoothProxy::dataReceived,          m_packetProcessor,  &PacketProcessor::processData);
    connect(m_bluetoothProxy,   &BluetoothProxy::disconnected,          m_plots,            &PlotWidget::clear);

    connect(m_odometry,         &OdometryWindow::reseted,               m_plots,            &PlotWidget::clear);

    connect(m_remoteSettings,   &MovementSettingsWidget::stepsUpdated,  m_remote,           &RemoteWidget::setSteps);

    m_remoteControlTab = new QTabWidget();
    m_remoteControlTab->addTab(m_table,         tr("Absolu"));
    m_remoteControlTab->addTab(m_remote,        tr("Relatif"));
    m_remoteControlTab->addTab(m_remoteSettings,tr("Paramètres"));

    m_robotSettingsTab = new QTabWidget();
    m_robotSettingsTab->addTab(m_odometry,  tr("Odometrie"));
    m_robotSettingsTab->addTab(m_asserv,    tr("Asservissement"));
    m_robotSettingsTab->addTab(m_watches,   tr("Watches"));

    m_tabs = new QTabWidget(this);
    m_tabs->addTab(m_bluetoothManagement,   tr("Bluetooth"));
    m_tabs->addTab(m_robotSettingsTab,      tr("Réglages"));
    m_tabs->addTab(m_remoteControlTab,      tr("Déplacements"));
    m_tabs->addTab(m_plots,                 tr("Graphes"));
    m_tabs->addTab(m_logger,                tr("Logs"));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_tabs);
#else

    BluetoothTestServer* server = new BluetoothTestServer(this);
#endif
}

void Magiks::connected()
{
    qDebug() << "Connected to remote device!";
}
