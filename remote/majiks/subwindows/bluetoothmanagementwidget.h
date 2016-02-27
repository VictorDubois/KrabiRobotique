#ifndef BLUETOOTHMANAGEMENTWIDGET_H
#define BLUETOOTHMANAGEMENTWIDGET_H

#include <QWidget>

class BluetoothProxy;
class QPushButton;

class BluetoothManagementWidget: public QWidget
{
    public:
        BluetoothManagementWidget(BluetoothProxy *bluetoothProxy, QWidget *parent = nullptr);

    private:
        void sendTest();

        QPushButton* m_scanButton;
        QPushButton* m_sendButton;

        BluetoothProxy* m_bluetoothProxy;
};

#endif // BLUETOOTHMANAGEMENTWIDGET_H
