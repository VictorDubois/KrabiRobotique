#include "odometriewindow.h"
#include "ui_odometriewindow.h"

#include "../bluetoothproxy/bluetoothproxy.h"

#include <cmath>

OdometrieWindow::OdometrieWindow(BluetoothProxy* bluetoothProxy, QWidget *parent): QWidget(parent), ui(new Ui::OdometrieWindow)
{
    ui->setupUi(this);

    m_bluetoothProxy = bluetoothProxy;

    connect(ui->queryButton,            &QPushButton::clicked,   this, &OdometrieWindow::requireSync);
    connect(ui->applyButton,            &QPushButton::clicked,   this, &OdometrieWindow::apply);
    connect(ui->resetButton,            &QPushButton::clicked,   this, &OdometrieWindow::resetRelatives);
    connect(ui->setWheelSizeFromX,      &QPushButton::clicked,   this, &OdometrieWindow::setWheelSizeFromX);
    connect(ui->setWheelSizeFromY,      &QPushButton::clicked,   this, &OdometrieWindow::setWheelSizeFromX);
    connect(ui->setInterAxisFromAngle,  &QPushButton::clicked,   this, &OdometrieWindow::setInterAxisFromAngle);

    resetRelatives();
}

OdometrieWindow::~OdometrieWindow()
{
    delete ui;
}

void OdometrieWindow::showEvent(QShowEvent*)
{
    requireSync();
}

void OdometrieWindow::addRelative(Position rp, Angle ra)
{
    m_rx += rp.x;
    m_ry += rp.y;
    m_rangle += ra;

    update();
}

void OdometrieWindow::addRelative(Vec2d rp, Angle ra)
{
    m_rx        += rp.x;
    m_ry        += rp.y;
    m_rangle    += ra;

    update();
}

void OdometrieWindow::settingsReceived(float wheelsize, float interaxis)
{
    ui->wheelSize->setValue(wheelsize);
    ui->interAxisDistance->setValue(interaxis);
}

void OdometrieWindow::resetRelatives()
{
    m_rx        = 0.f;
    m_ry        = 0.f;
    m_rangle    = 0.f;

    update();

    //DebugWindow::getInstance()->clearPlots();
    emit reseted();
}

void OdometrieWindow::requireSync()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_ODOMETRIE);
    m_bluetoothProxy->sendData(p);
}

void OdometrieWindow::update()
{
    ui->xRelativeLabel->setText(QString::number(m_rx));
    ui->yRelativeLabel->setText(QString::number(m_ry));
    ui->angleRelativeLabel->setText(QString::number(m_rangle));
}

void OdometrieWindow::setWheelSizeFromX()
{
    ui->wheelSize->setValue(ui->targetX->value() * ui->wheelSize->value() / m_rx);
}

void OdometrieWindow::setWheelSizeFromY()
{
    ui->wheelSize->setValue(ui->targetY->value() * ui->wheelSize->value() / m_ry);
}

void OdometrieWindow::setInterAxisFromAngle()
{
    ui->interAxisDistance->setValue(ui->targetAngle->value() * 3.1415f / 180.f * ui->interAxisDistance->value() / m_rangle);
}

void OdometrieWindow::apply()
{
    KrabiPacket p(KrabiPacket::SET_ODOMETRIE);
    p.add((float) ui->wheelSize->value());
    p.add((float) ui->interAxisDistance->value());

    m_bluetoothProxy->sendData(p);
}
