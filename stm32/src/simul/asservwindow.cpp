#include "asservwindow.h"
#include "ui_asservwindow.h"

#include "debugwindow.h"
#include "table.h"

AsservWindow::AsservWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AsservWindow)
{
    ui->setupUi(this);
}

AsservWindow::~AsservWindow()
{
    delete ui;
}

bool AsservWindow::graphLinear()
{
    return ui->linearGraph->isChecked();
}

bool AsservWindow::graphAngular()
{
    return ui->angularGraph->isChecked();
}

bool AsservWindow::graphDuty()
{
    return ui->dutyGraph->isChecked();
}

bool AsservWindow::clickGoto()
{
    return ui->clickGoto->isChecked();
}

void AsservWindow::settingsReceivedAngular(float p, float i, float d)
{
    ui->angKp->setValue(p);
    ui->angKi->setValue(i);
    ui->angKd->setValue(d);
}

void AsservWindow::settingsReceivedLinear(float p, float i, float d)
{
    ui->linKp->setValue(p);
    ui->linKi->setValue(i);
    ui->linKd->setValue(d);
}

void AsservWindow::requireSyncAngular()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_PID_ANG);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void AsservWindow::requireSyncLinear()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_PID_LIN);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void AsservWindow::runTest()
{
    KrabiPacket p(KrabiPacket::RUN_PID_TEST);
    p.add((float) ui->linSpeed->value());
    p.add((float) ui->angSpeed->value());
    p.add((float) ui->engineLimit->value());
    p.add((uint16_t) ui->duration->value());

    DebugWindow::getInstance()->clearPlots();

    DebugWindow::getInstance()->getBluetoothWindow()->send(p);

    Table::getMainInstance()->resetTimer();
}

void AsservWindow::stopTest()
{
    KrabiPacket p(KrabiPacket::STOP);
    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void AsservWindow::on_linQuery_clicked()
{
    requireSyncLinear();
}

void AsservWindow::on_linSet_clicked()
{
    KrabiPacket p(KrabiPacket::SET_PID_LIN);
    p.add((float) ui->linKp->value());
    p.add((float) ui->linKi->value());
    p.add((float) ui->linKd->value());
    p.add(ui->linearEnabled->isChecked());

    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void AsservWindow::on_angQuery_clicked()
{
    requireSyncAngular();
}

void AsservWindow::on_angSet_clicked()
{
    KrabiPacket p(KrabiPacket::SET_PID_ANG);
    p.add((float) ui->angKp->value());
    p.add((float) ui->angKi->value());
    p.add((float) ui->angKd->value());
    p.add(ui->angularEnabled->isChecked());

    DebugWindow::getInstance()->getBluetoothWindow()->send(p);
}

void AsservWindow::on_stopButton_clicked()
{
    stopTest();
}

void AsservWindow::on_runButton_clicked()
{
    runTest();
}

void AsservWindow::on_spinBox_valueChanged(int cycles)
{
    ui->durationLabel->setText(QString::number((float)cycles / 200.f));
}
