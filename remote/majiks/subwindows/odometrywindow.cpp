#include "odometrywindow.h"
#include "ui_odometrywindow.h"

#include "../bluetoothproxy/bluetoothproxy.h"

#include <cmath>

OdometryWindow::OdometryWindow(AbstractSerialProxy* serialProxy, QWidget *parent): QWidget(parent), ui(new Ui::OdometryWindow)
{
    ui->setupUi(this);

    m_serialProxy = serialProxy;

    connect(ui->queryButton,            &QPushButton::clicked,   this, &OdometryWindow::requireSync);
    connect(ui->applyButton,            &QPushButton::clicked,   this, &OdometryWindow::apply);
    connect(ui->resetButton,            &QPushButton::clicked,   this, &OdometryWindow::resetReferences);
    connect(ui->setWheelSizeFromX,      &QPushButton::clicked,   this, &OdometryWindow::setWheelSizeFromX);
    connect(ui->setWheelSizeFromY,      &QPushButton::clicked,   this, &OdometryWindow::setWheelSizeFromX);
    connect(ui->setInterAxisFromAngle,  &QPushButton::clicked,   this, &OdometryWindow::setInterAxisFromAngle);

    setCurrentRobotAngle(0.f);
    resetReferences();
}

OdometryWindow::~OdometryWindow()
{
    delete ui;
}

void OdometryWindow::showEvent(QShowEvent*)
{
    requireSync();
}


void OdometryWindow::settingsReceived(float wheelsize, float interaxis)
{
    ui->wheelSize->setValue(wheelsize);
    ui->interAxisDistance->setValue(interaxis);
}

void OdometryWindow::setCurrentRobotPosition(QPointF position)
{
    m_currentRobotPosition = position;
}

void OdometryWindow::setCurrentRobotAngle(float angle)
{
    m_currentRobotAngle = angle;
}

QPointF OdometryWindow::getRelativePosition() const
{
    return m_currentRobotPosition - m_referenceRobotPosition;
}

float OdometryWindow::getRelativeAngle() const
{
    return m_currentRobotAngle - m_referenceRobotAngle;
}

void OdometryWindow::resetReferences()
{
    m_referenceRobotAngle       = m_currentRobotAngle;
    m_referenceRobotPosition    = m_referenceRobotPosition;

    update();

    emit reseted();
}

void OdometryWindow::requireSync()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_ODOMETRIE);
    m_serialProxy->sendData(p);
}

void OdometryWindow::update()
{
    ui->xRelativeLabel->setText(QString::number(getRelativePosition().x()));
    ui->yRelativeLabel->setText(QString::number(getRelativePosition().y()));
    ui->angleRelativeLabel->setText(QString::number(getRelativeAngle()));
}

void OdometryWindow::setWheelSizeFromX()
{
    ui->wheelSize->setValue(ui->targetX->value() * ui->wheelSize->value() / getRelativePosition().x());
}

void OdometryWindow::setWheelSizeFromY()
{
    ui->wheelSize->setValue(ui->targetY->value() * ui->wheelSize->value() / getRelativePosition().y());
}

void OdometryWindow::setInterAxisFromAngle()
{
    ui->interAxisDistance->setValue(ui->targetAngle->value() * 3.1415f / 180.f * ui->interAxisDistance->value() / getRelativeAngle());
}

void OdometryWindow::apply()
{
    KrabiPacket p(KrabiPacket::SET_ODOMETRIE);
    p.add(static_cast<float>(ui->wheelSize->value()));
    p.add(static_cast<float>(ui->interAxisDistance->value()));

    m_serialProxy->sendData(p);
}
