#ifndef ODOMETRIEWINDOW_H
#define ODOMETRIEWINDOW_H

#include <QWidget>

#include "../../../stm32/include/position.h"

namespace Ui {
class OdometrieWindow;
}

class BluetoothProxy;

class OdometrieWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit OdometrieWindow(BluetoothProxy* bluetoothProxy, QWidget *parent = nullptr);
        ~OdometrieWindow();

        void addRelative(Position rp, Angle ra);
        void addRelative(Vec2d rp, Angle ra);
        void settingsReceived(float wheelsize, float interaxis);

        void update();

        void requireSync();

    signals:
        void reseted();

    protected:
        void showEvent(QShowEvent* event);

    private:
        void resetRelatives();
        void setWheelSizeFromX();
        void setWheelSizeFromY();
        void setInterAxisFromAngle();
        void apply();


        Ui::OdometrieWindow *ui;
        float m_rx;
        float m_ry;
        float m_rangle;

        BluetoothProxy* m_bluetoothProxy;
};

#endif // ODOMETRIEWINDOW_H
