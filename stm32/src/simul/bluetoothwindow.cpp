#include "bluetoothwindow.h"
#include "ui_bluetoothwindow.h"

#include "debugwindow.h"
#include "table.h"

#ifdef BLUETOOTH
    #include <qbluetoothaddress.h>
    #include <qbluetoothdevicediscoveryagent.h>
    #include <qbluetoothlocaldevice.h>
#endif
#include <QMenu>

BluetoothWindow::BluetoothWindow(QWidget *parent) :
    QWidget(parent),
#ifdef BLUETOOTH
    socket(NULL), discoveryAgent(new QBluetoothDeviceDiscoveryAgent()), localDevice(new QBluetoothLocalDevice()), serviceUUID(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB")),
#endif
    ui(new Ui::BluetoothWindow), mConnected(false), mConnecting(false)
{
    ui->setupUi(this);

    /*
     * In case of multiple Bluetooth adapters it is possible to set adapter
     * which will be used. Example code:
     *
     * QBluetoothAddress address("XX:XX:XX:XX:XX:XX");
     * discoveryAgent = new QBluetoothDeviceDiscoveryAgent(address);
     *
     **/

#ifdef BLUETOOTH
    connect(ui->scan, SIGNAL(clicked()), this, SLOT(startScan()));

    connect(discoveryAgent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(addDevice(QBluetoothDeviceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(scanFinished()));

    connect(ui->list, SIGNAL(itemActivated(QListWidgetItem*)),
            this, SLOT(itemActivated(QListWidgetItem*)));

    connect(ui->selectButton, SIGNAL(pressed()), this, SLOT(selectDevice()));

    /*connect(localDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
            this, SLOT(hostModeStateChanged(QBluetoothLocalDevice::HostMode)));*/

    setDevice(QBluetoothAddress("00:19:5D:EF:02:A5"), "Adaptater");
#endif

    //hostModeStateChanged(localDevice->hostMode());
    // add context menu for devices to be able to pair device
    /*ui->list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(displayPairingMenu(QPoint)));
    connect(localDevice, SIGNAL(pairingFinished(QBluetoothAddress,QBluetoothLocalDevice::Pairing))
        , this, SLOT(pairingDone(QBluetoothAddress,QBluetoothLocalDevice::Pairing)));*/

    //startScan();
    connectToDevice();
}

BluetoothWindow::~BluetoothWindow()
{
#ifdef BLUETOOTH
    delete discoveryAgent;
    delete localDevice;
#endif
    delete ui;
}

void BluetoothWindow::update()
{
    ui->statusLabel->setText(mConnected ? "Connected" : "Disconnected");
    DebugWindow::getInstance()->update();
}

void BluetoothWindow::bluetoothToggle()
{
    if (isConnecting() || isConnected())
        disconnect();
    else
        connectToDevice();

    update();
}

void BluetoothWindow::addDevice(const QBluetoothDeviceInfo &info)
{
#ifdef BLUETOOTH
    QString label = QString("%1 %2").arg(info.address().toString()).arg(info.name());
    QList<QListWidgetItem *> items = ui->list->findItems(label, Qt::MatchExactly);
    if (items.empty()) {
        QListWidgetItem *item = new QListWidgetItem(label);
        QBluetoothLocalDevice::Pairing pairingStatus = localDevice->pairingStatus(info.address());
        if (pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired )
            item->setTextColor(QColor(Qt::green));
        else
            item->setTextColor(QColor(Qt::black));

        ui->list->addItem(item);
    }
#endif
}

#ifdef BLUETOOTH
void BluetoothWindow::setDevice(QBluetoothAddress address, QString name)
{
    deviceAddress = address;
    deviceName = name;

    ui->labelDevice->setText(deviceName + "(" + deviceAddress.toString() + ")");
}
#endif

bool BluetoothWindow::isConnected()
{
    return mConnected;
}

bool BluetoothWindow::isConnecting()
{
    return mConnecting;
}

void BluetoothWindow::startScan()
{
#ifdef BLUETOOTH
    ui->list->clear();
    discoveryAgent->start();
    ui->scan->setEnabled(false);
#endif
}

void BluetoothWindow::scanFinished()
{
    ui->scan->setEnabled(true);
}

void BluetoothWindow::connected()
{
    mConnected = true;
    mConnecting = false;
    Table::getMainInstance()->setRemoteMod(true);
    update();
}

void BluetoothWindow::disconnected()
{
    mConnected = false;
    mConnecting = false;
    Table::getMainInstance()->setRemoteMod(false);
    update();
}

void BluetoothWindow::setGeneralUnlimited(bool unlimited)
{
#ifdef BLUETOOTH
    if (unlimited)
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
    else
        discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
#endif
}

void BluetoothWindow::selectDevice()
{
    QList<QListWidgetItem*> list = ui->list->selectedItems();
    if (list.size() > 0)
        itemActivated(list.front());
}

void BluetoothWindow::connectToDevice()
{
#ifdef BLUETOOTH
    if (deviceAddress.isNull())
        return;

    disconnect();

    if (socket == NULL)
    {
        socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

        connect(socket, SIGNAL(connected()), this, SLOT(connected()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
        connect(socket, SIGNAL(readChannelFinished()), this, SLOT(read()));
    }

    socket->connectToService(deviceAddress, QBluetoothUuid(serviceUUID), QIODevice::ReadWrite);
    mConnecting = true;
#endif
}

void BluetoothWindow::read()
{
#ifdef BLUETOOTH
    if (socket == NULL)
        return;

    bufferReceive.append(socket->readAll());

    for(int i(0); i<bufferReceive.size() - 1; ++i)
    {
        if (bufferReceive.at(i) == 0x0D && bufferReceive.at(i + 1) == 0x0A)
        {
            QByteArray packetBuffer = bufferReceive.left(i);
            if (i < KRABIPACKET_MAXSIZE)
            {
                KrabiPacket packet(packetBuffer);

                if (packet.isValid())
                    Table::getMainInstance()->treat(packet);
                else
#ifndef ROBOTHW
                    qDebug() << "Discard incorrect packet (checksum failure)";
#endif
            }

            bufferReceive = bufferReceive.right(bufferReceive.size() - (i + 2));
            i = 0;
        }
    }
#endif
}

void BluetoothWindow::send(KrabiPacket &packet)
{
#ifdef BLUETOOTH
    QByteArray a = packet.dataByteArray();
    a.append(0x0D);
    a.append(0x0A);

#ifndef ROBOTHW
    qDebug() << socket->write(a) << "written !";
#endif
#endif
}

void BluetoothWindow::disconnect()
{
#ifdef BLUETOOTH
    if (socket != NULL)
        socket->close();

    mConnected = false;
    mConnecting = false;
#endif
}

void BluetoothWindow::itemActivated(QListWidgetItem *item)
{
#ifdef BLUETOOTH
    QString text = item->text();

    int index = text.indexOf(' ');

    if (index == -1)
        return;

    QBluetoothAddress address(text.left(index));
    QString name(text.mid(index + 1));

    setDevice(address, name);

    /*ServiceDiscoveryDialog d(name, address);
    d.exec();*/
#endif
}

void BluetoothWindow::on_discoverable_clicked(bool clicked)
{
#ifdef BLUETOOTH
    if (clicked)
        localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
#endif
}

void BluetoothWindow::on_power_clicked(bool clicked)
{
#ifdef BLUETOOTH
    if (clicked)
        localDevice->powerOn();
    else
        localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
#endif
}

/*void BluetoothWindow::hostModeStateChanged(QBluetoothLocalDevice::HostMode mode)
{
    if (mode != QBluetoothLocalDevice::HostPoweredOff)
        ui->power->setChecked(true);
    else
       ui->power->setChecked( false);

    if (mode == QBluetoothLocalDevice::HostDiscoverable)
        ui->discoverable->setChecked(true);
    else
        ui->discoverable->setChecked(false);

    bool on = !(mode == QBluetoothLocalDevice::HostPoweredOff);


    ui->scan->setEnabled(on);
    ui->discoverable->setEnabled(on);
}

/*void BluetoothWindow::displayPairingMenu(const QPoint &pos)
{
    QMenu menu(this);
    QAction *pairAction = menu.addAction("Pair");
    QAction *removePairAction = menu.addAction("Remove Pairing");
    QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
    QListWidgetItem *currentItem = ui->list->currentItem();

    QString text = currentItem->text();
    int index = text.indexOf(' ');
    if (index == -1)
        return;

    QBluetoothAddress address (text.left(index));
    if (chosenAction == pairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
    } else if (chosenAction == removePairAction) {
        localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
    }
}
void BluetoothWindow::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

    if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::green));
        }
    } else {
        for (int var = 0; var < items.count(); ++var) {
            QListWidgetItem *item = items.at(var);
            item->setTextColor(QColor(Qt::red));
        }
    }
}*/
