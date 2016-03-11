#include "bluetoothmanagementwidget.h"

#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>

#include <QDebug>

#include "../bluetoothproxy/bluetoothproxy.h"

BluetoothManagementWidget::BluetoothManagementWidget(BluetoothProxy* bluetoothProxy, QWidget* parent): SerialManagementWidget(parent)
{
    m_bluetoothProxy = bluetoothProxy;

    m_bluetoothAvLabel      = new QLabel(this);
    m_connectionLabel       = new QLabel(this);

    //Debug
    m_sendButton            = new QPushButton(tr("Send"), this);

    m_scanButton            = new QPushButton(tr("Scan"), this);
    m_connectButton         = new QPushButton(this);
    m_checkBluetoothButton  = new QPushButton(tr("Check Bluetooth"), this);

    m_UUIDInput             = new QLineEdit(this);
    m_UUIDInput->setAlignment(Qt::AlignHCenter);
    m_UUIDInput->setValidator(new QRegExpValidator(QRegExp("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$")));

    m_detectedDevices = new QTableWidget(this);
    m_detectedDevices->insertColumn(0);
    m_detectedDevices->insertColumn(1);
    m_detectedDevices->setHorizontalHeaderLabels(QStringList() << tr("Device") << tr("Address"));
    m_detectedDevices->horizontalHeader()->setStretchLastSection(true);
    m_detectedDevices->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_detectedDevices->setSortingEnabled(true);

    QHBoxLayout* btAvLay = new QHBoxLayout;
    btAvLay->addWidget(m_bluetoothAvLabel);
    btAvLay->addWidget(m_checkBluetoothButton);

    QHBoxLayout* btCxLay = new QHBoxLayout;
    btCxLay->addWidget(m_connectionLabel);
    btCxLay->addWidget(m_connectButton);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(btAvLay);
    layout->addWidget(new QLabel(tr("UUID:")));
    layout->addWidget(m_UUIDInput);
    layout->addLayout(btCxLay);
    layout->addWidget(m_scanButton);
    layout->addWidget(m_detectedDevices);
    layout->addWidget(m_sendButton);

    connect(m_connectButton,        &QPushButton::clicked,              this,               &BluetoothManagementWidget::on_connectButton_clicked);
    connect(m_checkBluetoothButton, &QPushButton::clicked,              this,               &BluetoothManagementWidget::checkBluetoothAvailability);

    if(m_bluetoothProxy)
    {
        connect(m_scanButton,           &QPushButton::clicked,              m_bluetoothProxy,   &BluetoothProxy::scanRemoteDevices);
        connect(m_bluetoothProxy,       &BluetoothProxy::deviceDiscovered,  this,               &BluetoothManagementWidget::deviceDiscovered);
        connect(m_bluetoothProxy,       &BluetoothProxy::connected,         this,               &BluetoothManagementWidget::checkConnectionStatus);
        connect(m_bluetoothProxy,       &BluetoothProxy::disconnected,      this,               &BluetoothManagementWidget::checkConnectionStatus);
    }

    connect(m_UUIDInput,            &QLineEdit::textChanged,            this,               &BluetoothManagementWidget::changeUUID);

    //Debug
    connect(m_sendButton, &QPushButton::clicked, this, &BluetoothManagementWidget::sendTest);

    m_UUIDInput->setText("B62C4E8D-62CC-404B-BBBF-BF3E3BBB1374");

    checkConnectionStatus();
    checkBluetoothAvailability();
}

void BluetoothManagementWidget::changeUUID(const QString& uuid)
{
    if(m_bluetoothProxy)
        m_bluetoothProxy->setUUID(uuid);
}

void BluetoothManagementWidget::deviceDiscovered(const QString& name, const QString& address)
{
    m_detectedDevices->setSortingEnabled(false);

    qDebug() << "Found device " << name << " " << address;

    int idx = findDeviceByAddress(address);

    if(idx == -1)
    {
        idx = m_detectedDevices->rowCount();
        m_detectedDevices->insertRow(idx);
        m_detectedDevices->verticalHeader()->hide();
    }

    m_detectedDevices->setItem(idx, 0, new QTableWidgetItem(name));
    m_detectedDevices->setItem(idx, 1, new QTableWidgetItem(address));


    m_detectedDevices->item(idx, 1)->setData(BluetoothManagementWidget::ADDRESS_DATA_INDEX, address);
    m_detectedDevices->item(idx, 0)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    m_detectedDevices->item(idx, 1)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    m_detectedDevices->setSortingEnabled(true);
}

int BluetoothManagementWidget::findDeviceByAddress(const QString& address)
{
    for(int i = 0; i < m_detectedDevices->rowCount(); ++i)
        if(m_detectedDevices->item(i, 1)->data(BluetoothManagementWidget::ADDRESS_DATA_INDEX).toString() == address)
            return i;
    return -1;
}

void BluetoothManagementWidget::checkBluetoothAvailability()
{
    bool btAv = false;

    if(m_bluetoothProxy)
        btAv = m_bluetoothProxy->isBluetoothAvailable();

    m_scanButton->setEnabled(btAv);
    m_sendButton->setEnabled(btAv);
    m_detectedDevices->setEnabled(btAv);
    m_connectButton->setEnabled(btAv);
    m_UUIDInput->setEnabled(btAv);

    m_bluetoothAvLabel->setText(tr("Bluetooth is <b>%1available</b>").arg(btAv?"":"NOT "));
}

void BluetoothManagementWidget::checkConnectionStatus()
{   
    bool cxSt = false;

    if(m_bluetoothProxy)
        cxSt = m_bluetoothProxy->isConnected();

    m_UUIDInput->setEnabled(!cxSt);

    if(cxSt)
    {
        m_connectionLabel->setText(tr("Connected to <b>%1</b>").arg(m_bluetoothProxy->remoteAddress()));
        m_connectButton->setText(tr("Disconnect"));
    }
    else
    {
        m_connectionLabel->setText(tr("Not connected"));
        m_connectButton->setText(tr("Connect to device"));
    }
}

void BluetoothManagementWidget::on_connectButton_clicked()
{
    if(!m_bluetoothProxy)
        return;

    if(m_bluetoothProxy->isConnected())
        return m_bluetoothProxy->disconnect();

    QString address(getSelectedAddress());

    if(!address.isEmpty())
        m_bluetoothProxy->connectToHost(address);
}

QString BluetoothManagementWidget::getSelectedAddress() const
{
    auto l = m_detectedDevices->selectedItems();
    if(l.isEmpty())
        return QString();

    int row = l[0]->row();

    return m_detectedDevices->item(row, 1)->data(BluetoothManagementWidget::ADDRESS_DATA_INDEX).toString();
}


//Debug
void BluetoothManagementWidget::sendTest()
{
    if(!m_bluetoothProxy)
        return;

    KrabiPacket packet(KrabiPacket::LOG_DEBUG);
    packet.addString("test");

    m_bluetoothProxy->sendData(packet);
}
