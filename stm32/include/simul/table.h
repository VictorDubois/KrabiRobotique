#ifndef TABLE_H_INCLUDED
#define TABLE_H_INCLUDED

#include <QWidget>
#include <QTime>

#include <Box2D.h>

#include "TableGraphics.h"
#include "XMLReader.h"
#include "sensors.h"
//#include "bougie.h"
//#include "v1-archive/singleton.h"
#include "position.h"
#include "robot.h"
#include "contactlistener.h"
#include "objet.h"

#include "krabipacket.h"

class MainWindow;

class Table : public QWidget//, public Singleton<Table>
{
Q_OBJECT
    //friend class Singleton<Table>;
private:
	int dt;
    std::vector<Objet*> objets;
    std::vector<Robot*> robots;

	b2World world;
	b2Body* tableBody;
	TableGraphics tableGraphics;
    ContactListener contactListenerTable;

    bool mHideTable, mDisplayRoute, mDisplayStrategy, mRemoteMod;

    long mTimerAdjust;

	void addCard(unsigned int n, int column);
    MainWindow* mainWindow;

    QImage robotRoute;

    QTime mTime;

    static Table* _instance;

public slots:
    void createObjects();
    void removeAllObjects();
    void hideTable(bool hidden);
    void displayRoute(bool display);
    void displayStrategy(bool display);
    void setRemoteMod(bool remote);

public:
	static const int tableWidth = 3000;
    static const int tableHeight = 2000;
	static b2AABB getWorldAABB();
    //Bougie p_bougies[20];
    //Bougie p_balles[20];
	//static const int tableWidth = 2100;
	//static const int tableHeight = 3000;

    static Table* getMainInstance();

    Table(MainWindow* mainWindow, QWidget* parent = 0, bool isYellow = true);
	virtual ~Table();

    void treat(KrabiPacket &packet);
    void watch(KrabiPacket &packet);

    void resetTimer();

    void update(int dt);
	void paintEvent(QPaintEvent* evt);
	void keyPressEvent(QKeyEvent* evt, bool press);
    void mousePressEvent(QMouseEvent* evt, bool press);

    float getDistanceToObject(Position pos);
    void removeClosestObject(Position pos);
    Robot* getMainRobot();

    float getCurrentTime();

    bool isInRemoteMod();

    void clearRoute();

    std::vector<Objet*> findObjectsNear(Position pos, Distance searchRadius = 0., Objet::Type type = Objet::ANY);


};

#endif

