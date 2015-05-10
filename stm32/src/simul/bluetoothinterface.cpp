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

void BluetoothInterface::log(QString message, bool debug)
{
    ui->debugBrowser->append((debug ? "[Debug] " : "") + message);
}
