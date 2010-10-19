#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include <QMainWindow>

class MainWindow: public QMainWindow
{
public:
	virtual ~MainWindow();
	MainWindow();
private:
	Q_OBJECT

	class Table* table;
	int dt;

private slots:
	void update();
protected:
	void resizeEvent(QResizeEvent* event);
};

#endif

