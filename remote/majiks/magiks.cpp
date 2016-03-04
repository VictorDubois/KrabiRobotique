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
#include "subwindows/odometriewindow.h"
#include "subwindows/asservwindow.h"
#include "subwindows/graphwindow.h"
#include "subwindows/watchwindow.h"
#include "subwindows/loggerwidget.h"
#include "subwindows/plotwidget.h"
#include "subwindows/tablewidget.h"
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
    m_odometrie             = new OdometrieWindow(m_bluetoothProxy);
    m_asserv                = new AsservWindow(m_bluetoothProxy);
    m_watches               = new WatchWindow(m_bluetoothProxy);
    m_graphs                = new GraphWindow();
    m_logger                = new LoggerWidget();
    m_plots                 = new PlotWidget();
    m_table                 = new TableWidget(m_bluetoothProxy);

    m_packetProcessor = new PacketProcessor(m_odometrie, m_graphs, m_watches, m_asserv, m_logger);

    connect(m_bluetoothProxy, &BluetoothProxy::connected,           this, &Magiks::connected);

    connect(m_bluetoothProxy, &BluetoothProxy::dataReceived, m_packetProcessor, &PacketProcessor::processData);

    connect(m_odometrie,        &OdometrieWindow::reseted,      m_plots, &PlotWidget::clear);
    connect(m_packetProcessor,  &PacketProcessor::reseted,      m_plots, &PlotWidget::clear);
    connect(m_bluetoothProxy,   &BluetoothProxy::disconnected,  m_plots, &PlotWidget::clear);

    m_tabs = new QTabWidget(this);
    m_tabs->addTab(m_bluetoothManagement,   tr("Bluetooth"));
    m_tabs->addTab(m_odometrie,             tr("Odometrie"));
    m_tabs->addTab(m_asserv,                tr("Asservissement"));
    m_tabs->addTab(m_table,                 tr("Déplacements"));
    m_tabs->addTab(m_watches,               tr("Watches"));
    m_tabs->addTab(m_graphs,                tr("Graphes A"));
    m_tabs->addTab(m_plots,                 tr("Graphes B"));
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
