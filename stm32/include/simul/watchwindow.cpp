#include "watchwindow.h"
#include "ui_watchwindow.h"

WatchWindow::WatchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WatchWindow)
{
    ui->setupUi(this);
}

WatchWindow::~WatchWindow()
{
    delete ui;
}
