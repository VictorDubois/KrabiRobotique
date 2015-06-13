#ifndef ODOMETRIEWINDOW_H
#define ODOMETRIEWINDOW_H

#include <QWidget>

#include "position.h"

namespace Ui {
class OdometrieWindow;
}

class OdometrieWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OdometrieWindow(QWidget *parent = 0);
    ~OdometrieWindow();

    void addRelative(Position rp, Angle ra);
    void addRelative(Vec2d rp, Angle ra);
    void settingsReceived(float wheelsize, float interaxis);

    void update();

public slots:
    void requireSync();

private slots:
    void resetRelatives();
    void setWheelSizeFromX();
    void setWheelSizeFromY();
    void setInterAxisFromAngle();
    void apply();

private:
    Ui::OdometrieWindow *ui;
    float rx, ry, rangle;

    void showEvent(QShowEvent* event );
};

#endif // ODOMETRIEWINDOW_H
