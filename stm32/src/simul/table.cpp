#include "simul/table.h"
#include "simul/robot.h"
#include "element.h"
#include "cstdlib"
#include "time.h"
#include "strategieV2.h"

#include "main_window.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

#define PI 3.14159265358979323846264338327950
//#include <iostream>
#include <QPainter>
//#include "commandGoTo.h"

#include <cmath>

Table* Table::_instance = NULL;

Table* Table::getMainInstance()
{
    return _instance;
}

Position getCase(unsigned int i, unsigned int j)
{
    return Position(450 + i*350, j*350);
}

Position getCaseCenter(unsigned int i, unsigned int j)
{
    return Position(625 + i*350, 175 + j*350);
}

b2AABB Table::getWorldAABB()
{
	b2AABB a;
    a.lowerBound.Set(0,0);
    a.upperBound.Set(tableWidth, tableHeight);
	return a;
}

Table::Table(MainWindow *mainWi, QWidget* parent, bool isYellow): QWidget(parent),
    #ifdef BOX2D_2_0_1
        world(getWorldAABB(),b2Vec2(0.f,0.f), false))
    #else
        world(b2Vec2(0.f,0.f))
    #endif
{
    _instance = this;

    mHideTable          = false;
    mDisplayRoute       = false;
    mDisplayStrategy    = true;
    mRemoteMod          = false;
    mTimerAdjust        = 0;

    mainWindow          = mainWi;

    mTime.start();
    robotRoute = QImage(tableWidth, tableHeight, QImage::Format_ARGB32);

    contactListenerTable = ContactListener();
    world.SetContactListener(&contactListenerTable);
	dt=0;
	setAutoFillBackground(true);

	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);

    // ####### création des robots ######
    //Robot à nous
    robots.push_back(new Robot(world, false, isYellow)); // une seule odometrie, il faut donc mettre ce robot en dernier (celui commandé par la strat)

    //195,1760
    //Robot adversaire
    robots.push_back(new Robot(world, true, !isYellow));




    createObjects();

	//Geometry
	b2BodyDef bodyDef;
    bodyDef.position.Set(0., 0.);

	tableBody = world.CreateBody(&bodyDef);


#ifdef BOX2D_2_0_1
	b2PolygonDef box;
	b2PolygonDef &fixture = box;
#else
	b2PolygonShape box;
	b2FixtureDef fixture;
	fixture.shape = &box;
#endif
	fixture.friction = 0.5;
	fixture.density = 0;

#ifdef BOX2D_2_0_1
#define CreateFixture CreateShape
#endif
	// bordures
    box.SetAsBox(30,0, b2Vec2(0,0),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(0,20, b2Vec2(0,0),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(0,20, b2Vec2(30,0),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(30,0, b2Vec2(0,20),0);
    tableBody->CreateFixture(&fixture);
    // fin bordures

    // load the graphics of the game.

#ifdef KRABI2016
    tableGraphics.load("../paprikaSimulateur/tabledata2016.xml");
#elif GOLDO2018
    tableGraphics.load("../paprikaSimulateur/tabledata.xml");
#endif
    tableGraphics.createSolids(tableBody);


}

Table::~Table()
{
    for (unsigned int i = 0; i<robots.size();i++)
        delete robots[i];
    for (unsigned int i = 0; i<objets.size();i++)
        delete objets[i];
}

#ifdef GOLDO2018
void Table::createConstructionCubes(Position  position) {
    Position  cubeOffset =  Position(-29,-29);
    Position fiveCubesOffsets[5] = {
        Position(-58,+0),
        Position(+58,+0),
        Position(+0,+0),
        Position(+0,-58),
        Position(+0,+58)
    };
    QColor fiveCubesColors[5] = {
        QColor(97, 153, 59),
        QColor(208, 93, 40),
        QColor(14, 14, 16),
        QColor(0, 124, 176),
        QColor(247, 181, 0)
    };

    for (int i = 0; i < 5; i++) {
        objets.push_back(new Objet(world, position + fiveCubesOffsets[i] + cubeOffset, Objet::SANDCUBE, 0, fiveCubesColors[i]));
    }
}
#endif

void Table::createObjects()
{
    removeAllObjects();

#ifdef GOLDO2018
    createConstructionCubes(Position(2700.,1190.));
    createConstructionCubes(Position(2150.,540.));
    createConstructionCubes(Position(1900.,1500.));
    createConstructionCubes(Position(1100.,1500.));
    createConstructionCubes(Position(850.,540.));
    createConstructionCubes(Position(300.,1190.));
#endif

#ifdef KRABI2016

    /*objets.push_back(new Objet(world, Position(928.,2000.), Objet::FILET, 0, QColor(255, 0, 0)));*/


    //SANDCUBE
   objets.push_back(new Objet(world, Position(592.,842.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(650.,842.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(592.,900.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(650.,900.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));


    objets.push_back(new Objet(world, Position(2292.,842.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2350.,842.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2292.,900.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2350.,900.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(0.,0.), Objet::SANDCUBE1, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1225.,0.), Objet::SANDCUBE1, 0, QColor(232, 140, 0)));


    objets.push_back(new Objet(world, Position(1471.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1413.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1355.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1297.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1239.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1529.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1587.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1645.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1703.,0.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1471.,58.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1413.,58.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));

    objets.push_back(new Objet(world, Position(1529.,58.), Objet::SANDCUBE, 0, QColor(232, 140, 0)));


//SANDCYLINDER
    objets.push_back(new Objet(world, Position(1500.,145.), Objet::SANDCYLINDER, 0, QColor(232, 140, 0)));
  /*objets.push_back(new Objet(world, Position(650.,900.), Objet::SANDCYLINDER, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2350.,900.), Objet::SANDCYLINDER, 0, QColor(232, 140, 0)));
  objets.push_back(new Objet(world, Position(888.,58.), Objet::SANDCYLINDER, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2113.,58.), Objet::SANDCYLINDER, 0, QColor(232, 140, 0)));
    //SANDCONE

   objets.push_back(new Objet(world, Position(650.,900.), Objet::SANDCONE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2350.,900.), Objet::SANDCONE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(888.,58.), Objet::SANDCONE, 0, QColor(232, 140, 0)));
    objets.push_back(new Objet(world, Position(2113.,58.), Objet::SANDCONE, 0, QColor(232, 140, 0)));*/

    //PORTE
    objets.push_back(new Objet(world, Position(0.,0.), Objet::PORTE, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(2100.,0.), Objet::PORTE, 0, QColor(54, 103, 53)));
    /*objets.push_back(new Objet(world, Position(0.,0.), Objet::MER, 0, QColor(135,206,250)));
    //POISSON
    objets.push_back(new Objet(world, Position(650.,2020.), Objet::POISSON, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(2700.,1985.), Objet::POISSON, 0, QColor(54, 103, 53)));*/


#define SHELL_2
#ifdef SHELL_1
    //Coquillages neutres
    objets.push_back(new Objet(world, Position(2800.,1250.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(2800.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1500.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1500.,1850.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(200.,1250.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(200.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));

    //Coquillages verts
    objets.push_back(new Objet(world, Position(2100.,1450.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(1200.,1650.), Objet::SHELL, 0, QColor(54, 103, 53)));

    //Coquillages violets
    objets.push_back(new Objet(world, Position(1800.,1650.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(900.,1450.), Objet::SHELL, 0, QColor(132, 76, 130)));

#endif
#ifdef SHELL_2
    //Coquillages neutres
    objets.push_back(new Objet(world, Position(2800.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1500.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1500.,1850.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(200.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));

    //Coquillages verts
    objets.push_back(new Objet(world, Position(2800.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2100.,1450.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(1800.,1650.), Objet::SHELL, 0, QColor(54, 103, 53)));


    //Coquillages violets
    objets.push_back(new Objet(world, Position(900.,1450.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(1200.,1650.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
#endif
#ifdef SHELL_3
    //Coquillages neutres
    objets.push_back(new Objet(world, Position(2800.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(2300.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(700.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(200.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    //Coquillages verts
    objets.push_back(new Objet(world, Position(2800.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2300.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(1800.,1650.), Objet::SHELL, 0, QColor(54, 103, 53)));

    //Coquillages violets
    objets.push_back(new Objet(world, Position(1200.,1650.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(700.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));

#endif
#ifdef SHELL_4
    //Coquillages neutres
    objets.push_back(new Objet(world, Position(2300.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1800.,1650.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(1200.,1650.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(700.,1550.), Objet::SHELL, 0, QColor(241, 240, 234)));

    //Coquillages verts
    objets.push_back(new Objet(world, Position(2800.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2800.,1550.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2300.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));


    //Coquillages violets
    objets.push_back(new Objet(world, Position(700.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1550.), Objet::SHELL, 0, QColor(132, 76, 130)));
#endif
#ifdef SHELL_5
    //Coquillages neutres
    objets.push_back(new Objet(world, Position(2300.,1850.), Objet::SHELL, 0, QColor(241, 240, 234)));
    objets.push_back(new Objet(world, Position(700.,1850.), Objet::SHELL, 0, QColor(241, 240, 234)));

    //Coquillages verts
    objets.push_back(new Objet(world, Position(2800.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2800.,1550.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(2300.,1250.), Objet::SHELL, 0, QColor(54, 103, 53)));
    objets.push_back(new Objet(world, Position(700.,1550.), Objet::SHELL, 0, QColor(54, 103, 53)));


    //Coquillages violets
    objets.push_back(new Objet(world, Position(700.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1250.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(200.,1550.), Objet::SHELL, 0, QColor(132, 76, 130)));
    objets.push_back(new Objet(world, Position(2300.,1550.), Objet::SHELL, 0, QColor(132, 76, 130)));

#endif
#endif
}

void Table::removeAllObjects()
{
    for (unsigned int i = 0; i<objets.size();i++)
        delete objets[i];
    objets.clear();
}

void Table::hideTable(bool hidden)
{
    mHideTable = hidden;
}

void Table::displayRoute(bool display)
{
    mDisplayRoute = display;
}

void Table::displayStrategy(bool display)
{
    mDisplayStrategy = display;
}

void Table::clearRoute()
{
    robotRoute = QImage(tableWidth, tableHeight, QImage::Format_ARGB32);
}

void Table::setRemoteMod(bool remote)
{
    mRemoteMod = remote;
    getMainRobot()->setRemoteMod(mRemoteMod);

    if (mRemoteMod)
    {
        if (DebugWindow::getInstance()->getBluetoothWindow()->isConnected())
        {
            KrabiPacket p(KrabiPacket::REMOTE_MOD_SET);
            DebugWindow::getInstance()->getBluetoothWindow()->send(p);

            DebugWindow::getInstance()->getOdometrieWindow()->requireSync();
        }
        else
        {
            DebugWindow::getInstance()->getBluetoothWindow()->connectToDevice();
        }
    }
    else if (DebugWindow::getInstance()->getBluetoothWindow()->isConnected())
    {
        KrabiPacket p(KrabiPacket::REMOTE_MOD_RESET);
        //DebugWindow::getInstance()->getBluetoothWindow()->send
    }
}

bool Table::isInRemoteMod()
{
    return mRemoteMod;
}

float Table::getCurrentTime()
{
    return mRemoteMod ? (mTime.elapsed() + mTimerAdjust) / 1000. : StrategieV2::getTimeSpent()/1000.;
}

void Table::treat(KrabiPacket &packet)
{
    switch(packet.id())
    {
    case KrabiPacket::LOG_NORMAL:
        DebugWindow::getInstance()->getBluetoothInterface()->log(packet.getString());
        break;
    case KrabiPacket::LOG_DEBUG:
        DebugWindow::getInstance()->getBluetoothInterface()->log(packet.getString(), true);
        break;
    case KrabiPacket::WATCH_VARIABLE:
        watch(packet);
        break;
    case KrabiPacket::ASSERV_RESULT:
    {
        uint32_t time = packet.get<uint32_t>();
        float vitesseLin = packet.get<float>();
        float vitesseLinE = packet.get<float>();
        float linearDuty = packet.get<float>();
        float vitesseAng = packet.get<float>();
        float vitesseAngE = packet.get<float>();
        float angularDuty = packet.get<float>();

#ifndef ROBOTHW
        qDebug() << "Krabi Results" << time;
#endif

        if (time == 0)
            DebugWindow::getInstance()->clearPlots();
        if (DebugWindow::getInstance()->getAsservWindow()->graphLinear())
        {
            DebugWindow::getInstance()->plot(0, "Linear Speed", vitesseLin, time);
            DebugWindow::getInstance()->plot(1, "Linear Target", vitesseLinE, time);
        }
        if (DebugWindow::getInstance()->getAsservWindow()->graphAngular())
        {
            DebugWindow::getInstance()->plot(2, "Angular Speed", vitesseAng, time);
            DebugWindow::getInstance()->plot(3, "Angular Target", vitesseAngE, time);
        }
        if (DebugWindow::getInstance()->getAsservWindow()->graphDuty())
        {
            DebugWindow::getInstance()->plot(6, "Linear Duty", linearDuty, time);
            DebugWindow::getInstance()->plot(7, "Angular Duty", angularDuty, time);
        }
        break;
    }
    case KrabiPacket::TIME_SYNC:
    {
        int t = packet.get<uint16_t>();

        long diff = t - (mTime.elapsed() + mTimerAdjust);

        if (abs(diff) > 25)
        {
            #ifndef ROBOTHW
            qDebug() << "Timer sync error" << diff << "ms";
            #endif
        }

        /*if (diff < -1500)
        {
            DebugWindow::getInstance()->clearPlots();
            qDebug() << "Timer restart";
        }*/

        mTimerAdjust = t - mTime.elapsed();
        //qDebug() << "Timer" << t << t / 1000 << t % 1000;
        break;
    }
    default:
        qDebug() << "Uncaught packet : " << packet.id() << packet.length();
        break;
    }
}

void Table::watch(KrabiPacket &packet)
{
    uint16_t type = packet.get<uint16_t>();

    switch(type)
    {
    case KrabiPacket::W_POSITION:
    {
        float x = packet.get<float>();
        float y = packet.get<float>();
        float ang = packet.get<float>();

        PositionPlusAngle newPos = PositionPlusAngle(Position(x, y), ang);

        getMainRobot()->setPos(newPos);
        if (previousPosition)
            DebugWindow::getInstance()->getOdometrieWindow()->addRelative(newPos.position - previousPos.position, newPos.angle - previousPos.angle);
        previousPos = newPos;
        previousPosition = true;
        break;
    }
    case KrabiPacket::W_SPEED:
    {
        float l = packet.get<float>();
        float a = packet.get<float>();
        DebugWindow::getInstance()->plot(0, "Linear Speed", l);
        DebugWindow::getInstance()->plot(1, "Angular Speed", a * 100.);
        break;
    }
    case KrabiPacket::W_SPEED_TARGET:
    {
        float l = packet.get<float>();
        float a = packet.get<float>();
        DebugWindow::getInstance()->plot(2, "Linear Target", l);
        DebugWindow::getInstance()->plot(3, "Angular Target", a * 100.);
        break;
    }
    case KrabiPacket::W_PID_ANG:
    {
        float p = packet.get<float>();
        float i = packet.get<float>();
        float d = packet.get<float>();

        DebugWindow::getInstance()->getAsservWindow()->settingsReceivedAngular(p, i, d);
        break;
    }
    case KrabiPacket::W_PID_LIN:
    {
        float p = packet.get<float>();
        float i = packet.get<float>();
        float d = packet.get<float>();

        DebugWindow::getInstance()->getAsservWindow()->settingsReceivedLinear(p, i, d);
        break;
    }
    case KrabiPacket::W_ODOMETRIE:
    {
        float wheelsize = packet.get<float>();
        float interaxis = packet.get<float>();

        DebugWindow::getInstance()->getOdometrieWindow()->settingsReceived(wheelsize, interaxis);
        break;
    }
    case KrabiPacket::W_WATCHES:
        DebugWindow::getInstance()->getWatchWindow()->syncFinished(packet);
        break;
    case KrabiPacket::W_SHARPS:
        DebugWindow::getInstance()->getSharpWindow()->syncFinished(packet);
        break;
    default:
        #ifndef ROBOTHW
        qDebug() << "Uncaught watch : " << type;
        #endif
        break;
    }
}

void Table::resetTimer()
{
    DebugWindow::getInstance()->clearPlots();
    mTimerAdjust = -mTime.elapsed();
}

void Table::update(int dt)
{
    //exit(0);
	this->dt = dt;
	for(unsigned int i=0; i < robots.size(); i++)
	{
		robots[i]->updateForces(dt);
       // robots[i]->interact(elements);

       // std::cout << Odometrie::odometrie->getPos().getPosition().getX() << " " <<  Odometrie::odometrie->getPos().getPosition().getY() << std::endl;
	}
    /*if (dt) {
        QPoint posBougie, posMarteau, tester;
        for (unsigned int i = 12; i < 20; i++) {
            posBougie = p_bougies[i].getPosition();
            posMarteau = robots[0]->getLeftUpperHammerPos();
            tester = QPoint(posBougie - posMarteau );
            if (tester.manhattanLength() < 40)
                p_balles[i].setColor(QColor(0,128,255));
            posBougie = p_bougies[i].getPosition();
            posMarteau = robots[0]->getRightUpperHammerPos();
            tester = QPoint(posBougie - posMarteau );
            if (tester.manhattanLength() < 40)
                p_balles[i].setColor(QColor(0,128,255));
        }
        for (unsigned int i = 0; i < 12; i++) {
            posBougie = p_bougies[i].getPosition();
            posMarteau = robots[0]->getLeftLowerHammerPos();
            tester = QPoint(posBougie - posMarteau );
            if (tester.manhattanLength() < 40)
                p_balles[i].setColor(QColor(0,128,255));
            posBougie = p_bougies[i].getPosition();
            posMarteau = robots[0]->getRightLowerHammerPos();
            tester = QPoint(posBougie - posMarteau );
            if (tester.manhattanLength() < 40)
                p_balles[i].setColor(QColor(0,128,255));
        }
    }*/

    //route
    QPainter painter(&robotRoute);
    painter.setPen(QPen(Qt::red, 8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    Position posRobot = getMainRobot()->getPos().getPosition();

    painter.drawPoint(posRobot.x, posRobot.y);

    QString debugText = "Robot Position :\n";
    QString sharpsChecked = "";

    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        if (StrategieV2::getSharpsToCheck()[i])
            sharpsChecked.append((!sharpsChecked.isEmpty() ? QString(", ") : QString()) + QString::number(i));

    debugText += "   x : " + QString::number(getMainRobot()->getPos().position.getX()) + " mm\n";
    debugText += "   y : " + QString::number(getMainRobot()->getPos().position.getY()) + " mm\n";
    debugText += "   angle : " + QString::number(getMainRobot()->getPos().getAngle()*180/M_PI) + " °\n\n";

    debugText += "Robot Speeds :\n";
    debugText += "   lin : " + QString::number(getMainRobot()->getVitesseLineaire()) + " \n";
    debugText += "   ang : " + QString::number(getMainRobot()->getVitesseAngulaire()) + " \n\n";

    debugText += "Time : " + QString::number(mRemoteMod ? (mTime.elapsed() + mTimerAdjust) / 1000. : StrategieV2::getTimeSpent()/1000.) + " s\n\n";

    debugText += "Sharps : \n " + sharpsChecked + "\n\n";

    debugText += "Detected beacons: \n";
    PositionsList l = Tourelle::getSingleton()->getPositionsList();
    if(!l.isEmpty())
    {
        for(size_t i=0;i<l.size();++i)
            debugText += ("Distance: " + QString::number(l[i].distance) + "mm Angle: " + QString::number(l[i].angle) + " degs\n");
        debugText += "\n";
    }
    else
        debugText += "None\n\n";

    DebugWindow::getInstance()->setText(debugText);
    if (!mRemoteMod)
    {
        DebugWindow::getInstance()->plot(0, "Linear Speed", robots[1]->getVitesseLineaire());
        DebugWindow::getInstance()->plot(1, "Angular Speed", robots[1]->getVitesseAngulaire() * 100.);
    }

#ifdef BOX2D_2_0_1
	world.Step((float)dt/1000., 10);
#else
	world.Step((float)dt/1000., 10, 10);
	world.ClearForces();
#endif
	for(unsigned int i=0; i < objets.size(); i++)
		objets[i]->updatePos();
	repaint();
}

void Table::paintEvent(QPaintEvent* evt)
{

	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing,true);
    //p.setWindow(QRect(0,-tableHeight,tableWidth,tableHeight));
    p.setWindow(QRect(0,0,tableWidth,tableHeight));
	p.setWorldMatrixEnabled(true);


//    mHideTable = true;
	// dessine la table
    if (!mHideTable)
    {

#ifdef GOLDO2018
        QPixmap pixmap1("../paprikaSimulateur/fond2018.png");
        p.drawPixmap(0, 0, tableWidth, tableHeight, pixmap1);  // this works
#endif
        tableGraphics.draw(&p);

    }
    else
    {
        QFont font;
        font.setPixelSize(24);
        p.setFont(font);

        p.setOpacity(1);
        p.setPen(QColor(Qt::gray));
        p.fillRect(QRect(0, 0, tableWidth, tableHeight), QBrush(Qt::gray));

        // draw a grid
        // 100 mm
        p.setOpacity(0.25);
        p.setPen(QColor(Qt::white));

        for(int i(100); i < tableWidth; i+=100)
            p.drawLine(QPoint(i, 0), QPoint(i, tableHeight));
        for(int i(100); i < tableHeight; i+=100)
            p.drawLine(QPoint(0, i), QPoint(tableWidth, i));

        // 200 mm
        p.setOpacity(0.5);
        p.setPen(QColor(Qt::white));

        for(int i(0); i < tableWidth; i+=200)
        {
            p.setPen(QColor(Qt::white));
            p.drawLine(QPoint(i, 0), QPoint(i, tableHeight));
            p.setPen(QColor(Qt::black));
            p.drawText(QPoint(i + 16, 32), QString::number(i));
        }
        for(int i(0); i < tableHeight; i+=200)
        {
            p.setPen(QColor(Qt::white));
            p.drawLine(QPoint(0, i), QPoint(tableWidth, i));
            p.setPen(QColor(Qt::black));
            p.drawText(QPoint(16, i), QString::number(i));
        }

        // 1000 mm
        p.setOpacity(1);
        p.setPen(QColor(Qt::black));

        for(int i(1000); i < tableWidth; i+=1000)
            p.drawLine(QPoint(i, 0), QPoint(i, tableHeight));
        for(int i(1000); i < tableHeight; i+=1000)
            p.drawLine(QPoint(0, i), QPoint(tableWidth, i));
    }

    if (mDisplayRoute)
        p.drawImage(0, 0, robotRoute);

    for (unsigned int i=0; i < objets.size(); i++)
        objets[i]->paint(p);

    /*for(unsigned int i=0; i < 20; i++)
        p_bougies[i].draw(p);

    for(unsigned int i=0; i < 20; i++)
        p_balles[i].draw(p);*/

	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->paint(p,dt);

	dt = 0;

    // Dessin d'un trajet
   /* PositionPlusAngle** path = CommandGoTo::path();
    	p.setPen(QColor(Qt::black));
	if (path)
	{
		for(unsigned int i=0; i+1 < PATH_LENGTH; i++)
		p.drawLine(path[i]->position.x, -path[i]->position.y, path[i+1]->position.x, -path[i+1]->position.y);
    CommandGoTo::deletePath(path);
    }*/

    // On dessine le graphe de la strat
    if(mDisplayStrategy)
    {
        this->getMainRobot()->paintStrategie(p);
    }

    /*QFont font;
    font.setPixelSize(50);
    p.setFont(font);
    p.setOpacity(1);
    p.setPen(QColor("krabicolor"));
    //p.setBrush(QBrush("black"));
    p.drawText( QPoint(2625,100), "Pos X : ");
    p.drawText( QPoint(2800,100), QString::number(robots[1]->getPos().position.getX()));
    p.drawText( QPoint(2625,200), "Pos Y : ");
    p.drawText( QPoint(2800,200), QString::number(robots[1]->getPos().position.getY()));
    p.drawText( QPoint(2625,300), "Angle : ");
    p.drawText( QPoint(2800,300), QString::number(robots[1]->getPos().getAngle()*180/M_PI));
    p.drawText( QPoint(2625,400), "Timer : ");
    p.drawText( QPoint(2800,400), QString::number(StrategieV2::getTimeSpent()/1000.) + " s");

    p.drawText( QPoint(2625,500), "Check Sharps: ");
    QString sharpsChecked = "";

    for (int i = 0; i < SharpSensor::END_SHARP_NAME; i++)
        if (StrategieV2::getSharpsToCheck()[i])
            sharpsChecked.append((!sharpsChecked.isEmpty() ? QString(", ") : QString()) + QString::number(i));

    p.drawText( QPoint(2625,600), sharpsChecked);*/

    evt->ignore();
}

void Table::keyPressEvent(QKeyEvent* evt, bool press)
{
	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->keyPressEvent(evt, press);


    Sensors::getSensors()->keyPressEvent(evt,press);
}

void Table::mousePressEvent(QMouseEvent* evt, bool)
{
    float x = (evt->x()/900.0) * tableWidth;
    float y = (evt->y()/600.0) * tableHeight;
#ifndef ROBOTH
    qDebug() << "X : " << x << "    -    Y : " << y;
#endif

    if (evt->button() == Qt::RightButton && DebugWindow::getInstance()->getAsservWindow()->clickGoto())
    {
        #ifndef ROBOTH
        qDebug() << "Send the robot !";
        #endif

        KrabiPacket p(KrabiPacket::RUN_GOTO);
        p.add((float) x);
        p.add((float) y);
        p.add((float) -1.f);

        DebugWindow::getInstance()->getBluetoothWindow()->send(p);
    }
}

Position getSideElemCenter(bool right, unsigned int elem)
{
	return Position(right ? 200 : 2800, 1810 - elem*280);
}
float Table::getDistanceToObject(Position pos)
{
    float min = 1000000;
    for (unsigned int i = 0 ; i < objets.size(); i++)
    {
        if ((objets[i]->getPosition() - pos).getNorme() < min)
            min = (objets[i]->getPosition() - pos).getNorme();
    }
    return min;
}

void Table::removeClosestObject(Position pos)
{
    int minID = -1;
    float min = 1000000;
    for (unsigned int i = 0 ; i < objets.size(); i++)
    {
        if ((objets[i]->getPosition() - pos).getNorme() < min)
        {
            minID = i;
            min = (objets[i]->getPosition() - pos).getNorme();
        }
    }
    if (minID > 0)
    {
        objets.erase(objets.begin()+minID);
    }
}

Robot* Table::getMainRobot()
{
    return robots.front();
}

std::vector<Objet*> Table::findObjectsNear(Position pos, Distance searchRadius, Objet::Type type)
{
    std::vector<Objet*> r;

    for(std::vector<Objet*>::iterator it = objets.begin(); it != objets.end(); ++it)
    {
        if ((type == Objet::ANY || (*it)->getType() == type) && (*it)->isNear(pos, searchRadius))
            r.push_back(*it);
    }

    return r;
}

QList<PositionData> Table::getBeaconsRelativePosition(Robot* refBot)
{
    refBot = (!refBot)?getMainRobot():refBot;

    Position refPosition = refBot->getPos().getPosition();
    float refAngle       = refBot->getPos().getAngle();

    QList<PositionData> positions;

    for(size_t i = 0; i < robots.size(); ++i)
    {
        if(robots[i] == refBot)
            continue;


        float x = (refPosition - robots[i]->getPos().getPosition()).x;
        float y = (refPosition - robots[i]->getPos().getPosition()).y;

        PositionData polarPosition;
        polarPosition.distance = sqrt(x*x+y*y);
        polarPosition.angle = static_cast<unsigned long>((atan2(y, x) + refAngle) * 180.f / 3.1415f)%360;

        positions.append(polarPosition);
    }

    return positions;
}
