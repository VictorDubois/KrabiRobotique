#include "sharpwindow.h"
#include "ui_sharpwindow.h"

SharpWindow::SharpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SharpWindow)
{
    ui->setupUi(this);
}

SharpWindow::~SharpWindow()
{
    delete ui;
}
