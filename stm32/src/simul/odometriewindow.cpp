#include "odometriewindow.h"
#include "ui_odometriewindow.h"

#include "debugwindow.h"

#include <math.h>

OdometrieWindow::OdometrieWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OdometrieWindow), rx(0.), ry(0.), rangle(0.)
{
    ui->setupUi(this);

    connect(ui->queryButton, SIGNAL(clicked(bool)), this, SLOT(requireSync()));
    connect(ui->applyButton, SIGNAL(clicked(bool)), this, SLOT(apply()));
    connect(ui->resetButton, SIGNAL(clicked(bool)), this, SLOT(resetRelatives()));
    connect(ui->setWheelSizeFromX, SIGNAL(clicked(bool)), this, SLOT(setWheelSizeFromX()));
    connect(ui->setWheelSizeFromY, SIGNAL(clicked(bool)), this, SLOT(setWheelSizeFromX()));
    connect(ui->setInterAxisFromAngle, SIGNAL(clicked(bool)), this, SLOT(setInterAxisFromAngle()));

    update();
}

OdometrieWindow::~OdometrieWindow()
{
    delete ui;
}

void OdometrieWindow::showEvent(QShowEvent* event )
{
    requireSync();
}

void OdometrieWindow::addRelative(Position rp, Angle ra)
{
    rx += rp.x;
    ry += rp.y;
    rangle += ra;

    update();
}

void OdometrieWindow::settingsReceived(float wheelsize, float interaxis)
{
    ui->wheelSize->setValue(wheelsize);
    ui->interAxisDistance->setValue(interaxis);
}

void OdometrieWindow::resetRelatives()
{
    rx = 0.;
    ry = 0.;
    rangle = 0.;

    update();

    DebugWindow::getInstance()->clearPlots();
}

void OdometrieWindow::requireSync()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_ODOMETRIE);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void OdometrieWindow::update()
{
    ui->xRelativeLabel->setText(QString::number(rx));
    ui->yRelativeLabel->setText(QString::number(ry));
    ui->angleRelativeLabel->setText(QString::number(rangle));
}

void OdometrieWindow::setWheelSizeFromX()
{
    ui->wheelSize->setValue(ui->targetX->value() * ui->wheelSize->value() / rx);
}

void OdometrieWindow::setWheelSizeFromY()
{
    ui->wheelSize->setValue(ui->targetY->value() * ui->wheelSize->value() / ry);
}

void OdometrieWindow::setInterAxisFromAngle()
{
    ui->interAxisDistance->setValue(ui->targetAngle->value() * M_PI / 180.f * ui->interAxisDistance->value() / rangle);
}

void OdometrieWindow::apply()
{
    KrabiPacket p(KrabiPacket::SET_ODOMETRIE);
    p.add((float) ui->wheelSize->value());
    p.add((float) ui->interAxisDistance->value());

    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}
