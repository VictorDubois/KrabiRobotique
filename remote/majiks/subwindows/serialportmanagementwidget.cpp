#include "serialportmanagementwidget.h"

#include "serialproxy/serialproxy.h"

#include <QtSerialPort/QSerialPortInfo>

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QLayout>

SerialPortManagementWidget::SerialPortManagementWidget(SerialProxy *serialProxy, QWidget* parent): SerialManagementWidget(parent)
{
    m_serialProxy = serialProxy;

    m_statusLabel   = new QLabel(this);
    m_portsCB       = new QComboBox(this);
    m_refreshButton = new QPushButton(tr("Refresh"), this);
    m_connectButton = new QPushButton(this);

    m_portsCB->setEditable(false);

    connect(m_connectButton, &QPushButton::clicked, this, &SerialPortManagementWidget::on_connectButton_clicked);

    QHBoxLayout* portsLayout = new QHBoxLayout();
    portsLayout->addWidget(new QLabel(tr("Ports:"), this));
    portsLayout->addWidget(m_portsCB);
    portsLayout->addWidget(m_refreshButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->addLayout(portsLayout);
    mainLayout->addWidget(m_connectButton);
    mainLayout->addStretch();

    updateConnectionStatus();
    updateAvailablePorts();
}

void SerialPortManagementWidget::updateConnectionStatus()
{
    bool cxSt = false;

    if(m_serialProxy)
        cxSt = m_serialProxy->isOpen();

    if(cxSt)
    {
        m_connectButton->setText(tr("Disconnect from port"));
        m_statusLabel->setText(tr("Connected to <b>%1</b>").arg(m_serialProxy->getPortName()));
    }
    else
    {
        m_connectButton->setText(tr("Connect to port"));
        m_statusLabel->setText(tr("Not connected"));
    }
}

void SerialPortManagementWidget::updateAvailablePorts()
{
    QString current = getSelectedPort();

    QList<QSerialPortInfo> l = QSerialPortInfo::availablePorts();

    m_portsCB->clear();

    for(auto port: l)
        m_portsCB->addItem(port.portName());

    m_portsCB->setCurrentText(current);
}

QString SerialPortManagementWidget::getSelectedPort() const
{
    return m_portsCB->currentText();
}

void SerialPortManagementWidget::on_connectButton_clicked()
{
    if(!m_serialProxy)
        return;

    if(!m_serialProxy->isOpen())
    {
        QString port = getSelectedPort();

        if(port.isEmpty())
            return;

        m_serialProxy->open(port);
    }
    else
        m_serialProxy->close();

    updateConnectionStatus();
}
