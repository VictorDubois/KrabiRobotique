#ifndef ODOMETRIEWINDOW_H
#define ODOMETRIEWINDOW_H

#include <QWidget>

namespace Ui {
class OdometrieWindow;
}

class OdometrieWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OdometrieWindow(QWidget *parent = 0);
    ~OdometrieWindow();

private:
    Ui::OdometrieWindow *ui;
};

#endif // ODOMETRIEWINDOW_H
