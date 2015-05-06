#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QWidget>
#include <QLabel>

class MainWindow;

class DebugWindow : public QWidget
{
    Q_OBJECT
public:
    explicit DebugWindow(MainWindow *parent = 0);

    bool isAttached();
    void setReady(bool ready);

    void moveWithoutEvent(QPoint pos);

    void setText(QString text);
    
signals:
    
public slots:

private:
    virtual void moveEvent ( QMoveEvent * event );

    MainWindow *parent;
    bool attached, ready;

    QLabel* qlText;
    
};

#endif // DEBUGWINDOW_H
