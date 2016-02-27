#ifndef ASSERVWINDOW_H
#define ASSERVWINDOW_H

#include <QWidget>

namespace Ui {
class AsservWindow;
}

class BluetoothProxy;

class AsservWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit AsservWindow(BluetoothProxy* bluetoothProxy, QWidget *parent = 0);
        ~AsservWindow();

        bool graphLinear();
        bool graphAngular();
        bool graphDuty();

        bool clickGoto();

        void settingsReceivedAngular(float p, float i, float d);
        void settingsReceivedLinear(float p, float i, float d);
        void requireSyncAngular();
        void requireSyncLinear();
        void runTest();
        void stopTest();

    private:
        void on_linQuery_clicked();
        void on_linSet_clicked();
        void on_angQuery_clicked();
        void on_angSet_clicked();
        void on_stopButton_clicked();
        void on_runButton_clicked();
        void on_spinBox_valueChanged(int cycles);

        Ui::AsservWindow *ui;

        BluetoothProxy* m_bluetoothProxy;

        void showEvent(QShowEvent* event);
};

#endif // ASSERVWINDOW_H
