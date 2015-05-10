#ifndef BLUETOOTHWINDOW_H
#define BLUETOOTHWINDOW_H

#include <QWidget>
#include <QListWidgetItem>

#ifdef BLUETOOTH
    #include <qbluetoothsocket.h>
    #include <qbluetoothglobal.h>
    #include <qbluetoothlocaldevice.h>
#else
    class QBluetoothAddress;
    class QBluetoothDeviceInfo;
#endif

#include "krabipacket.h"

QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

namespace Ui {
class BluetoothWindow;
}

class BluetoothWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BluetoothWindow(QWidget *parent = 0);
    ~BluetoothWindow();

#ifdef BLUETOOTH
    void setDevice(QBluetoothAddress address, QString name);
#endif

    bool isConnected();
    bool isConnecting();

    void send(KrabiPacket &packet);

public slots:
    void addDevice(const QBluetoothDeviceInfo&);
    void on_power_clicked(bool clicked);
    void on_discoverable_clicked(bool clicked);
    //void displayPairingMenu(const QPoint &pos);
    //void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);
    void selectDevice();

    void connectToDevice();
    void disconnect();
    void read();

    void update();

private slots:
    void connected();
    void disconnected();
    void startScan();
    void scanFinished();
    void setGeneralUnlimited(bool unlimited);
    void itemActivated(QListWidgetItem *item);
    //void hostModeStateChanged(QBluetoothLocalDevice::HostMode);
    void bluetoothToggle();

private:
    QString deviceName;
#ifdef BLUETOOTH
    QBluetoothAddress deviceAddress;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
    const QString serviceUUID;
#endif
    Ui::BluetoothWindow *ui;

    QByteArray bufferReceive;

    bool mConnected, mConnecting;
};

#endif // BLUETOOTHWINDOW_H
