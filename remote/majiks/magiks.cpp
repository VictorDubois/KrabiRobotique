#include "magiks.h"

#ifdef BLUETOOTH_USING_WINSOCK
#include "bluetoothproxy/bluetoothproxywinsock.h"
#else
#include "bluetoothproxy/bluetoothproxyqt5.h"
#endif

#include "serialproxy/serialproxy.h"

#include <QTabWidget>
#include <QVBoxLayout>

#include "subwindows/bluetoothmanagementwidget.h"
#include "subwindows/serialportmanagementwidget.h"

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
#include <QMessageBox>
#include <QDebug>

Magiks::Magiks(QWidget *parent): QWidget(parent)
{
    setWindowTitle(tr("Magiks - Robot remote"));
#ifndef BLUETOOTH_SERVER_MODE

    bool bluetoothMode = (QMessageBox::question(this, tr("Mode"), tr("Do you want to use Majiks in Bluetooth mode?"))
                          == QMessageBox::Yes);

    if(bluetoothMode)
    {
        #ifdef BLUETOOTH_USING_WINSOCK
        m_serialProxy = new BluetoothProxyWinsock(this);
        #else
        m_serialProxy = new BluetoothProxyQt5(this);
        #endif
    }
    else
    {
        m_serialProxy = new SerialProxy(9600, this);
    }

    if(bluetoothMode)
        m_serialManagement   = new BluetoothManagementWidget(bluetoothMode?static_cast<BluetoothProxy*>(m_serialProxy):nullptr);
    else
        m_serialManagement   = new SerialPortManagementWidget(bluetoothMode?nullptr:static_cast<SerialProxy*>(m_serialProxy));

    m_odometry              = new OdometryWindow(m_serialProxy);
    m_asserv                = new AsservWindow(m_serialProxy);
    m_watches               = new WatchWindow(m_serialProxy);
    m_logger                = new LoggerWidget();
    m_plots                 = new PlotWidget();
    m_table                 = new TableWidget(m_serialProxy);
    m_remote                = new RemoteWidget(m_serialProxy);
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

    connect(m_serialProxy,   &AbstractSerialProxy::connected,             this,               &Magiks::connected);
    connect(m_serialProxy,   &AbstractSerialProxy::disconnected,          this,               &Magiks::disconnected);
    connect(m_serialProxy,   &AbstractSerialProxy::dataReceived,          m_packetProcessor,  &PacketProcessor::processData);
    connect(m_serialProxy,   &AbstractSerialProxy::disconnected,          m_plots,            &PlotWidget::clear);

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
    m_tabs->addTab(m_serialManagement,      tr("Connexion"));
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

void Magiks::disconnected()
{
    m_logger->log("Disconnected");
}

void Magiks::connected()
{
    m_logger->log("Connected");
}
