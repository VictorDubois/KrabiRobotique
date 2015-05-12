#ifndef ASSERVWINDOW_H
#define ASSERVWINDOW_H

#include <QWidget>

namespace Ui {
class AsservWindow;
}

class AsservWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AsservWindow(QWidget *parent = 0);
    ~AsservWindow();

    bool graphLinear();
    bool graphAngular();
    bool graphDuty();

    bool clickGoto();

public slots:
    void settingsReceivedAngular(float p, float i, float d);
    void settingsReceivedLinear(float p, float i, float d);
    void requireSyncAngular();
    void requireSyncLinear();
    void runTest();
    void stopTest();

private slots:
    void on_linQuery_clicked();

    void on_linSet_clicked();

    void on_angQuery_clicked();

    void on_angSet_clicked();

    void on_stopButton_clicked();

    void on_runButton_clicked();

    void on_spinBox_valueChanged(int cycles);

private:
    Ui::AsservWindow *ui;

    void showEvent(QShowEvent* event );
};

#endif // ASSERVWINDOW_H
