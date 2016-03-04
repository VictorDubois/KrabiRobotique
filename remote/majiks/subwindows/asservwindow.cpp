#include "asservwindow.h"
#include "ui_asservwindow.h"

#include "../bluetoothproxy/bluetoothproxy.h"

AsservWindow::AsservWindow(BluetoothProxy* bluetoothProxy, QWidget *parent): QWidget(parent), ui(new Ui::AsservWindow)
{
    ui->setupUi(this);
    m_bluetoothProxy = bluetoothProxy;
}

AsservWindow::~AsservWindow()
{
    delete ui;
}

void AsservWindow::showEvent(QShowEvent*)
{
    requireSyncAngular();
    requireSyncLinear();
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
    m_bluetoothProxy->sendData(p);
}

void AsservWindow::requireSyncLinear()
{
    KrabiPacket p(KrabiPacket::WATCH_REQUIRE_ONCE, KrabiPacket::W_PID_LIN);
    m_bluetoothProxy->sendData(p);
}

void AsservWindow::runTest()
{
    KrabiPacket p(KrabiPacket::RUN_PID_TEST);
    p.add((float) ui->linSpeed->value());
    p.add((float) ui->angSpeed->value());
    p.add((float) ui->engineLimit->value());
    p.add((uint16_t) ui->duration->value());

    //DebugWindow::getInstance()->clearPlots();

    m_bluetoothProxy->sendData(p);

    //Table::getMainInstance()->resetTimer();
}

void AsservWindow::stopTest()
{
    KrabiPacket p(KrabiPacket::STOP);
    m_bluetoothProxy->sendData(p);
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

    m_bluetoothProxy->sendData(p);
}

void AsservWindow::on_angQuery_clicked()
{
    requireSyncAngular();
}

void AsservWindow::on_angSet_clicked()
{
    KrabiPacket p(KrabiPacket::SET_PID_ANG);
    p.add(static_cast<float>(ui->angKp->value()));
    p.add(static_cast<float>(ui->angKi->value()));
    p.add(static_cast<float>(ui->angKd->value()));
    p.add(ui->angularEnabled->isChecked());

    m_bluetoothProxy->sendData(p);
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
