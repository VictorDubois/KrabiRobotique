#ifndef BLUETOOTHINTERFACE_H
#define BLUETOOTHINTERFACE_H

#include <QWidget>

namespace Ui {
class BluetoothInterface;
}

class BluetoothInterface : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothInterface(QWidget *parent = 0);
    ~BluetoothInterface();

public slots:
    void log(QString message, bool debug = false);

private:
    Ui::BluetoothInterface *ui;
};

#endif // BLUETOOTHINTERFACE_H
