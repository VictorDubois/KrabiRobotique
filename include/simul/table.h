#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <QWidget>

class Table : public QWidget
{
private:
	int dt;
public:
	std::vector<class Robot*> robots;

	static const int tableWidth = 3000;
	static const int tableHeight = 2100;
	//static const int tableWidth = 2100;
	//static const int tableHeight = 3000;

	Table(QWidget* widget);
	virtual ~Table();

	void update(int dt);
	void paintEvent(QPaintEvent* evt);
};

#endif

