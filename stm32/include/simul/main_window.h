#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
	virtual ~MainWindow();
	MainWindow();
private:

	class Table* table;
	int dt;

private slots:
	void update();
protected:
	void resizeEvent(QResizeEvent* event);
	void keyPressEvent(QKeyEvent* evt);
	void keyReleaseEvent(QKeyEvent* evt);
};

#endif

