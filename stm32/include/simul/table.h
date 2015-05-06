#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <QWidget>
#include <Box2D.h>
#include "TableGraphics.h"
#include "XMLReader.h"
#include "sensors.h"
//#include "bougie.h"
#include "v1-archive/singleton.h"
#include "position.h"
#include "robot.h"
#include "contactlistener.h"

class MainWindow;

class Table : public QWidget, public Singleton<Table>
{
    friend class Singleton<Table>;
private:
	int dt;
    std::vector<class Objet*> objets;
	std::vector<class Robot*> robots;

	b2World world;
	b2Body* tableBody;
	TableGraphics tableGraphics;
    ContactListener contactListenerTable;

	void addCard(unsigned int n, int column);
    MainWindow* mainWindow;

public:

	static const int tableWidth = 3000;
    static const int tableHeight = 2000;
	static b2AABB getWorldAABB();
    //Bougie p_bougies[20];
    //Bougie p_balles[20];
	//static const int tableWidth = 2100;
	//static const int tableHeight = 3000;

    Table(MainWindow* mainWindow, QWidget* parent = 0, bool isBlue = true);
	virtual ~Table();

    void update(int dt);
	void paintEvent(QPaintEvent* evt);
	void keyPressEvent(QKeyEvent* evt, bool press);
    void mousePressEvent(QMouseEvent* evt, bool press);

    float getDistanceToObject(Position pos);
    void removeClosestObject(Position pos);
    Robot* getMainRobot();
};

#endif

