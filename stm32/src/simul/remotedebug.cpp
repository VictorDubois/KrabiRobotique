#include "remotedebug.h"
#include "ui_remotedebug.h"

RemoteDebug::RemoteDebug(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteDebug)
{
    ui->setupUi(this);
}

RemoteDebug::~RemoteDebug()
{
    delete ui;
}
