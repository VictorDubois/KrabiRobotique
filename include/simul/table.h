#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <QWidget>
#include "element.h"

class Table : public QWidget
{
private:
	int dt;
	std::vector<class Element*> elements;
	std::vector<class Robot*> robots;
public:

	static const int tableWidth = 3000;
	static const int tableHeight = 2100;
	//static const int tableWidth = 2100;
	//static const int tableHeight = 3000;

	Table(QWidget* widget);
	virtual ~Table();

	void update(int dt);
	void paintEvent(QPaintEvent* evt);
	void keyPressEvent(QKeyEvent* evt, bool press);
};

#endif

