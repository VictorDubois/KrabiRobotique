#ifndef BLUETOOTHMANAGEMENTWIDGET_H
#define BLUETOOTHMANAGEMENTWIDGET_H

#include "serialmanagementwidget.h"

class BluetoothProxy;

class QPushButton;
class QTableWidget;
class QLabel;
class QLineEdit;

class BluetoothManagementWidget: public SerialManagementWidget
{
    public:
        BluetoothManagementWidget(BluetoothProxy *bluetoothProxy = nullptr, QWidget *parent = nullptr);

        QString getSelectedAddress() const;

    private:

        void checkBluetoothAvailability();
        void checkConnectionStatus();

        void deviceDiscovered(const QString& name, const QString& address);
        void on_connectButton_clicked();

        void changeUUID(const QString& uuid);

        // Find a device in the list by its address.
        // Returns -1 if none is found
        int findDeviceByAddress(const QString& address);

        // Qt::ItemDataRole index for device address
        // (allow for the stored data to be different from the display)
        const int ADDRESS_DATA_INDEX = (Qt::UserRole+10);

        QPushButton* m_scanButton;
        QPushButton* m_checkBluetoothButton;
        QPushButton* m_connectButton;

        QLabel* m_bluetoothAvLabel;
        QLabel* m_connectionLabel;

        QLineEdit* m_UUIDInput;

        QTableWidget* m_detectedDevices;

        BluetoothProxy* m_bluetoothProxy;
};

#endif // BLUETOOTHMANAGEMENTWIDGET_H
