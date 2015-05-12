#include "sharpwindow.h"
#include "ui_sharpwindow.h"

#include "debugwindow.h"

SharpWindow::SharpWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SharpWindow)
{
    ui->setupUi(this);

    ui->sharpsList->setRowCount(0);
    ui->sharpsList->setColumnCount(3);
    ui->sharpsList->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
    ui->sharpsList->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));
    ui->sharpsList->setHorizontalHeaderItem(2, new QTableWidgetItem("Detect"));
    ui->sharpsList->setColumnWidth(0, 250);
    ui->sharpsList->setColumnWidth(1, 60);
    ui->sharpsList->setColumnWidth(2, 60);
}

SharpWindow::~SharpWindow()
{
    delete ui;
}

void SharpWindow::setWatchChecked(bool checked)
{
    ui->watchCheckBox->setChecked(checked);
}

QString SharpWindow::getSharpName(SharpSensor::SharpName sharp)
{
    switch(sharp)
    {
    case SharpSensor::BACK_RIGHT:
        return "BACK_RIGHT";
    case SharpSensor::BACK_LEFT:
        return "BACK_LEFT";
    case SharpSensor::FRONT_LEFT:
        return "FRONT_LEFT";
    case SharpSensor::FRONT_RIGHT:
        return "FRONT_RIGHT";
    case SharpSensor::LEFT_FRONT:
        return "LEFT_FRONT";
    case SharpSensor::LEFT_BACK:
        return "LEFT_BACK";
    case SharpSensor::RIGHT_FRONT:
        return "RIGHT_FRONT";
    case SharpSensor::RIGHT_BACK:
        return "RIGHT_BACK";
    default:
        return "unknown";
    }
}

void SharpWindow::syncFinished(KrabiPacket p)
{
    ui->sharpsList->clear();
    ui->sharpsList->setRowCount(SharpSensor::END_SHARP_NAME);

    for(int i(0); i < SharpSensor::END_SHARP_NAME; ++i)
    {
        if (!p.isReadable<uint16_t>())
            break;

        SharpSensor::SharpName s = (SharpSensor::SharpName) i;
        uint16_t value = p.get<uint16_t>();
        bool on = p.get<bool>();
        ui->sharpsList->setItem(i, 0, new QTableWidgetItem(getSharpName(s)));
        ui->sharpsList->setItem(i, 1, new QTableWidgetItem(QString::number(value)));
        ui->sharpsList->setItem(i, 2, new QTableWidgetItem(on ? "Yes" : "No"));
    }
}

void SharpWindow::on_watchCheckBox_stateChanged(int arg1)
{
    DebugWindow::getInstance()->getWatchWindow()->setWatching(KrabiPacket::W_SHARPS, ui->watchCheckBox->isChecked());
}
