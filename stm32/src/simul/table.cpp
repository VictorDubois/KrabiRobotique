#include "simul/table.h"
#include "simul/robot.h"
#include "element.h"
#include "cstdlib"
#include "time.h"
#include "strategieV2.h"

#include "main_window.h"

#define COUPE_2015

#ifndef ROBOTHW
#include <QDebug>
#endif

#define PI 3.14159265358979323846264338327950
//#include <iostream>
#include <QPainter>
//#include "commandGoTo.h"

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

Table::Table(MainWindow *mainWindow, QWidget* parent, bool isBlue) :
    QWidget(parent), mainWindow(mainWindow), mHideTable(false), mDisplayRoute(false), mDisplayStrategy(true), mRemoteMod(false), mTimerAdjust(0), previousPosition(false),
#ifdef BOX2D_2_0_1
	world(getWorldAABB(),b2Vec2(0.f,0.f), false)
#else
    world(b2Vec2(0.f,0.f))
#endif
{
    _instance = this;

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
    int x_pos_Krabi = 300;//Proche
    int x_pos_Advsersaire = 2700;//Loin
    int angle_Krabi = 0;
    int angle_Adversaire = M_PI;

    if(isBlue)
    {
        x_pos_Krabi = 3000-x_pos_Krabi;
        x_pos_Advsersaire = 3000-x_pos_Advsersaire;
        angle_Krabi+=M_PI;
        angle_Adversaire+=M_PI;
    }
    //Robot adversaire
    robots.push_back(new Robot(world,PositionPlusAngle(Position(x_pos_Advsersaire,1000, isBlue), angle_Adversaire), true, !isBlue));
    //Robot à nous
    robots.push_back(new Robot(world,PositionPlusAngle(Position(x_pos_Krabi,1000, isBlue), angle_Krabi), false, isBlue)); // une seule odometrie, il faut donc mettre ce robot en dernier (celui commandé par la strat)
    //195,1760

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

#ifdef COUPE_2013
    // table 2013
    // plateaux blancs bords zones départ
    box.SetAsBox(4,1, b2Vec2(0,0),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(30,0),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(0,20),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(30,20),0);
    tableBody->CreateFixture(&fixture);

	// gateau
	b2CircleShape circle;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	circle.m_radius = 5.f;
    circle.m_p.Set(15.,20.);
	tableBody->CreateFixture(&fixtureDef);


#endif

#ifdef COUPE_2014
    // table 2014

    //Foyer central
    b2CircleShape foyerCentral;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &foyerCentral;
    foyerCentral.m_radius = 1.5;
    foyerCentral.m_p.Set(15.0,9.50);
    tableBody->CreateFixture(&fixtureDef);

    //Foyer rouge
    b2CircleShape foyerRouge;
    //b2FixtureDef fixtureDef;
    fixtureDef.shape = &foyerRouge;
    foyerRouge.m_radius = 2.5;
    foyerRouge.m_p.Set(0.0,0.0);
    tableBody->CreateFixture(&fixtureDef);

    //Foyer jaune
    b2CircleShape foyerJaune;
    //b2FixtureDef fixtureDef;
    fixtureDef.shape = &foyerJaune;
    foyerJaune.m_radius = 2.5;
    foyerJaune.m_p.Set(30.0,0.0);
    tableBody->CreateFixture(&fixtureDef);

    //Bloc dépose côté Jaune
    box.SetAsBox(3.5,0.65, b2Vec2(7.5,19.35),0);
    tableBody->CreateFixture(&fixture);
    box.SetAsBox(3.5,0.85, b2Vec2(7.5,17.85),0);
    tableBody->CreateFixture(&fixture);

    //Bloc dépose côté Rouge
    box.SetAsBox(3.5,0.65, b2Vec2(22.5,19.35),0);
    tableBody->CreateFixture(&fixture);
    box.SetAsBox(3.5,0.85, b2Vec2(22.5,17.85),0);
    tableBody->CreateFixture(&fixture);
#endif

	// load the graphics of the game.
    tableGraphics.load("../paprikaSimulateur/tabledata.xml");
    tableGraphics.createSolids(tableBody);

#ifdef COUPE_2013
    // création des bougies :
    QColor colors[20];
    colors[0] = QColor(0,0,255);
    colors[1] = QColor(255,0,0);
    colors[2] = QColor(255,0,0);
    colors[3] = QColor(0,0,255);
    colors[4] = QColor(255,255,255);
    colors[5] = QColor(255,255,255);
    colors[6] = QColor(255,255,255);
    colors[7] = QColor(255,255,255);
    colors[8] = QColor(255,0,0);
    colors[9] = QColor(0,0,255);
    colors[10] = QColor(0,0,255);
    colors[11] = QColor(255,0,0);
    colors[12] = QColor(0,0,255);
    colors[13] = QColor(255,0,0);
    colors[14] = QColor(0,0,255);
    colors[15] = QColor(255,0,0);
    colors[16] = QColor(0,0,255);
    colors[17] = QColor(255,0,0);
    colors[18] = QColor(0,0,255);
    colors[19] = QColor(255,0,0);

    for (int i = 0; i < 12; i++)
    {
        p_bougies[i] = Bougie(colors[i], QPointF(1500.f-450.f*cos((7.5+15.f*(float)(i))*PI/180.f), -2000.f+450.f*sin((7.5+15.f*(float)(i))*PI/180.f)), 40.f);
        //std::cout << "Position(" << 1500.f-700.f*cos((10+7.5+15.f*(float)(i))*PI/180.f) << ", " << 2000.f-700.f*sin((10+7.5+15.f*(float)(i))*PI/180.f) << "), " << wrapAngle((7.5+15.f*(float)(i))*PI/180.f-M_PI/2) << std::endl;
    }
    for (int i = 12; i < 20; i++)
    {
        p_bougies[i] = Bougie(colors[i], QPointF(1500.f-350.f*cos((11.25+22.5f*(float)(i-12))*PI/180.f), -2000.f+350.f*sin((11.25+22.5f*(float)(i-12))*PI/180.f)), 40.f);
        std::cout << "Position(" << 1500.f-700.f*cos((11.25+22.5f*(float)(i-12))*PI/180.f) << ", " << 2000.f-700.f*sin((11.25+22.5f*(float)(i-12))*PI/180.f) << "), " << wrapAngle((7.5+15.f*(float)(i))*PI/180.f-M_PI/2) << std::endl;
    }
    for (int i = 0; i < 12; i++)
    {
        p_balles[i] = Bougie(QColor(255,255,0), QPointF(1500.f-450.f*cos((7.5+15.f*(float)(i))*PI/180.f), -2000.f+450.f*sin((7.5+15.f*(float)(i))*PI/180.f)), 33.f);
    }
    for (int i = 12; i < 20; i++)
    {
        p_balles[i] = Bougie(QColor(255,255,0), QPointF(1500.f-350.f*cos((11.25+22.5f*(float)(i-12))*PI/180.f), -2000.f+350.f*sin((11.25+22.5f*(float)(i-12))*PI/180.f)), 33.f);
    }
#endif
}

Table::~Table()
{
    for (unsigned int i = 0; i<robots.size();i++)
        delete robots[i];
    for (unsigned int i = 0; i<objets.size();i++)
        delete objets[i];
}

void Table::createObjects()
{
    removeAllObjects();

    // ################################ Coupe 2014 ################################
#ifdef COUPE_2014
    //création des feux
    // côté rouge
    objets.push_back(new Objet(world, Position(885.,1470.), Objet::FIREUP, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(915.,330.), Objet::FIREUP, 3*PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(470.,915.), Objet::FIREUP, 0, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(0.,1270.), Objet::FIREUP, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(1370.,30.), Objet::FIREUP, 0, QColor(0, 0, 0)));

    //côté jaune
    objets.push_back(new Objet(world, Position(2085.,1470.), Objet::FIREUP, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2115.,330.), Objet::FIREUP, 3*PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2530.,885.), Objet::FIREUP, PI, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2970.,1270.), Objet::FIREUP, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(1630.,0.), Objet::FIREUP, PI, QColor(0, 0, 0)));

    //création des TORCHes
    //TORCHe rouge
    objets.push_back(new Objet(world, Position(900.,900.), Objet::TORCH, 0, QColor(108, 59, 42)));
    //TORCHe jaune
    objets.push_back(new Objet(world, Position(2100.,900.), Objet::TORCH, 0, QColor(108, 59, 42)));
#endif

    // ################################ Coupe 2013 ################################
#ifdef COUPE_2013
    //Verres 2013
    // côté bleu
    objets.push_back(new Objet(world, Position(900.,550.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1200.,550.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1050.,800.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1350.,800.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(900.,1050.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1200.,1050.), Objet::GLASS, 0, QColor(170, 170, 170)));

    // côté rouge
    objets.push_back(new Objet(world, Position(2100.,550.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1800.,550.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1950.,800.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1650.,800.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(2100.,1050.), Objet::GLASS, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1800.,1050.), Objet::GLASS, 0, QColor(170, 170, 170)));
#endif

    // ################################ Coupe 2015 ################################
#ifdef COUPE_2015
    //Gobelets à pop-corn
    objets.push_back(new Objet(world, Position(250.,1750.), Objet::CUP, 0, QColor(255, 255, 255)));
    objets.push_back(new Objet(world, Position(910.,800.), Objet::CUP, 0, QColor(255, 255, 255)));
    objets.push_back(new Objet(world, Position(1500.,1650.), Objet::CUP, 0, QColor(255, 255, 255)));
    objets.push_back(new Objet(world, Position(2090.,800.), Objet::CUP, 0, QColor(255, 255, 255)));
    objets.push_back(new Objet(world, Position(2750.,1750.), Objet::CUP, 0, QColor(255, 255, 255)));

    //Pieds verts
    objets.push_back(new Objet(world, Position(90.,200.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(90.,1750.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(90.,1850.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(850.,100.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(850.,200.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(870.,1355.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(1100.,1770.), Objet::STAND, 0, QColor(252, 189, 31)));
    objets.push_back(new Objet(world, Position(1300.,1400.), Objet::STAND, 0, QColor(252, 189, 31)));

    //Pieds jaunes
    objets.push_back(new Objet(world, Position(2910.,200.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(2910.,1750.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(2910.,1850.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(2150.,100.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(2150.,200.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(2130.,1355.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(1900.,1770.), Objet::STAND, 0, QColor(79, 168, 51)));
    objets.push_back(new Objet(world, Position(1700.,1400.), Objet::STAND, 0, QColor(79, 168, 51)));
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

    debugText += "   x : " + QString::number(robots[1]->getPos().position.getX()) + " mm\n";
    debugText += "   y : " + QString::number(robots[1]->getPos().position.getY()) + " mm\n";
    debugText += "   angle : " + QString::number(robots[1]->getPos().getAngle()*180/M_PI) + " °\n\n";

    debugText += "Robot Speeds :\n";
    debugText += "   lin : " + QString::number(robots[1]->getVitesseLineaire()) + " \n";
    debugText += "   ang : " + QString::number(robots[1]->getVitesseAngulaire()) + " \n\n";

    debugText += "Time : " + QString::number(mRemoteMod ? (mTime.elapsed() + mTimerAdjust) / 1000. : StrategieV2::getTimeSpent()/1000.) + " s\n\n";

    debugText += "Sharps : \n " + sharpsChecked + "\n\n";

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



	// dessine la table
    if (!mHideTable)
        tableGraphics.draw(&p);
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

void Table::mousePressEvent(QMouseEvent* evt, bool press)
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
    return robots.back();
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
