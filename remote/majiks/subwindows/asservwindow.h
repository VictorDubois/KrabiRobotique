#ifndef ASSERVWINDOW_H
#define ASSERVWINDOW_H

#include <QWidget>

namespace Ui {
class AsservWindow;
}

class AbstractSerialProxy;

class AsservWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit AsservWindow(AbstractSerialProxy* serialProxy, QWidget *parent = nullptr);
        ~AsservWindow();

        bool graphLinear();
        bool graphAngular();
        bool graphDuty();

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

        AbstractSerialProxy* m_serialProxy;

        void showEvent(QShowEvent* event);
};

#endif // ASSERVWINDOW_H
