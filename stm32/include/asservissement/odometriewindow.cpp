#include "odometriewindow.h"
#include "ui_odometriewindow.h"

OdometrieWindow::OdometrieWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OdometrieWindow)
{
    ui->setupUi(this);
}

OdometrieWindow::~OdometrieWindow()
{
    delete ui;
}
