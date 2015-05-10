#include "bluetoothinterface.h"
#include "ui_bluetoothinterface.h"

BluetoothInterface::BluetoothInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothInterface)
{
    ui->setupUi(this);
}

BluetoothInterface::~BluetoothInterface()
{
    delete ui;
}
