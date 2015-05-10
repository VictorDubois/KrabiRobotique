#include "bluetoothwindow.h"
#include "ui_bluetoothwindow.h"

BluetoothWindow::BluetoothWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BluetoothWindow)
{
    ui->setupUi(this);
}

BluetoothWindow::~BluetoothWindow()
{
    delete ui;
}
