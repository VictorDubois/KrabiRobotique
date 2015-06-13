#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>
#include <QTimer>
#include "debugwindow.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
	virtual ~MainWindow();
    MainWindow(bool isYellow);

private:
	class Table* table;
	int dt;

    QTimer postStartTimer;

    void moveEvent(QMoveEvent * event);
    void closeEvent(QCloseEvent *event);

private slots:
    void postStart();
	void update();

protected:
	void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent* evt);
	void keyPressEvent(QKeyEvent* evt);
	void keyReleaseEvent(QKeyEvent* evt);
};

#endif

