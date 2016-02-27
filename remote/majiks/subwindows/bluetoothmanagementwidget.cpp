#include "bluetoothmanagementwidget.h"

#include <QPushButton>
#include <QVBoxLayout>

#include "../bluetoothproxy/bluetoothproxy.h"

BluetoothManagementWidget::BluetoothManagementWidget(BluetoothProxy* bluetoothProxy, QWidget* parent): QWidget(parent)
{
    m_bluetoothProxy = bluetoothProxy;

    m_scanButton = new QPushButton(tr("Scan"), this);
    m_sendButton = new QPushButton(tr("Send"), this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(m_scanButton);
    layout->addWidget(m_sendButton);


    connect(m_scanButton, &QPushButton::clicked, m_bluetoothProxy, &BluetoothProxy::scanRemoteDevices);
    connect(m_sendButton, &QPushButton::clicked, this, &BluetoothManagementWidget::sendTest);
}


void BluetoothManagementWidget::sendTest()
{
    KrabiPacket packet(KrabiPacket::LOG_DEBUG);
    packet.addString("test");

    m_bluetoothProxy->sendData(packet);
}
