#include "asservwindow.h"
#include "ui_asservwindow.h"

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
