#ifndef SHARPWINDOW_H
#define SHARPWINDOW_H

#include <QWidget>

#include "sharpSensor.h"

#include "krabipacket.h"

namespace Ui {
class SharpWindow;
}

class SharpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SharpWindow(QWidget *parent = 0);
    ~SharpWindow();

    void setWatchChecked(bool checked);
    void syncFinished(KrabiPacket p);

    static QString getSharpName(SharpSensor::SharpName sharp);

private slots:
    void on_watchCheckBox_stateChanged(int arg1);

private:
    Ui::SharpWindow *ui;
};

#endif // SHARPWINDOW_H
