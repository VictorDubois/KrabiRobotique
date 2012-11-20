#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <QWidget>
#include <Box2D.h>
#include "TableGraphics.h"
#include "XMLReader.h"


class Table : public QWidget
{
private:
	int dt;
    std::vector<class Objet*> objets;
	std::vector<class Robot*> robots;

	b2World world;
	b2Body* tableBody;
	TableGraphics tableGraphics;

	void addCard(unsigned int n, int column);
public:

	static const int tableWidth = 3000;
	static const int tableHeight = 2000;
	static b2AABB getWorldAABB();
	//static const int tableWidth = 2100;
	//static const int tableHeight = 3000;

	Table(QWidget* widget);
	virtual ~Table();

	void update(int dt);
	void paintEvent(QPaintEvent* evt);
	void keyPressEvent(QKeyEvent* evt, bool press);
};

#endif

