#include "simul/table.h"
#include "simul/robot.h"
#include "simul/objet.h"
#include "element.h"
#include "cstdlib"
#include "time.h"

#define PI 3.14159265358979323846264338327950
#include <iostream>
#include <QPainter>
//#include "commandGoTo.h"

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
    //2013
    a.lowerBound.Set(0,0);
    a.upperBound.Set(tableWidth, tableHeight);
    //2014
    //a.lowerBound.Set(102,102);
    //a.upperBound.Set(tableWidth-127, tableHeight-127);
	return a;
}

Table::Table(QWidget* parent) :
	QWidget(parent),
#ifdef BOX2D_2_0_1
	world(getWorldAABB(),b2Vec2(0.f,0.f), false)
#else
//	world(b2Vec2(0.f,0.f), false)
    world(b2Vec2(0.f,0.f))
    //world(b2Vec2(127.0,102.0))
#endif
{
	dt=0;
	setAutoFillBackground(true);

	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);

    //création des robots
    robots.push_back(new Robot(world,PositionPlusAngle(Position(3000-270,560), M_PI), true));
    robots.push_back(new Robot(world,PositionPlusAngle(Position(95,1360, true), 0), false)); // une seule odometrie, il faut donc mettre ce robot en dernier (celui commandé par la strat)

    //création des feux
    // côté rouge
    objets.push_back(new Objet(world, Position(885.,1470.), Objet::fireUp, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(915.,470.), Objet::fireUp, 3*PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(330.,915.), Objet::fireUp, 0, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(0.,1270.), Objet::fireUp, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(1370.,30.), Objet::fireUp, 0, QColor(0, 0, 0)));

    //côté jaune
    objets.push_back(new Objet(world, Position(2085.,1470.), Objet::fireUp, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2115.,470.), Objet::fireUp, 3*PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2530.,885.), Objet::fireUp, PI, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(2970.,1270.), Objet::fireUp, PI/2, QColor(0, 0, 0)));
    objets.push_back(new Objet(world, Position(1630.,0.), Objet::fireUp, PI, QColor(0, 0, 0)));

    //création des torches
    //torche rouge
    objets.push_back(new Objet(world, Position(900.,900.), Objet::torch, 0, QColor(108, 59, 42)));
    //torche jaune
    objets.push_back(new Objet(world, Position(2100.,900.), Objet::torch, 0, QColor(108, 59, 42)));
    //Verres 2012l
    /* // côté bleu
    objets.push_back(new Objet(world, Position(900.,550.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1200.,550.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1050.,800.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1350.,800.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(900.,1050.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1200.,1050.), Objet::glass, 0, QColor(170, 170, 170)));

	// côté rouge
    objets.push_back(new Objet(world, Position(2100.,550.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1800.,550.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1950.,800.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1650.,800.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(2100.,1050.), Objet::glass, 0, QColor(170, 170, 170)));
    objets.push_back(new Objet(world, Position(1800.,1050.), Objet::glass, 0, QColor(170, 170, 170)));
    */



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

    /* table 2013
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

    */
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

    /*
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

*/
	// load the graphics of the game.
    tableGraphics.load("/home/alex/Documents/Krabi/gitRobotique/simulation/qtcreator-files/paprikaSimulateur/tabledata.xml");
    //tableGraphics.load("tabledata.xml");
    //2013
    tableGraphics.addYOffset(-tableHeight);
    // tableGraphics.addYOffset();
    //2014
    //tableGraphics.addYOffset(-tableHeight+102); // because we want the (0,0) point to be at the bottom left.
    //tableGraphics.addXOffset(+150); // because we want the (0,0) point to be at the bottom left.


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
}

Table::~Table()
{
    for (unsigned int i = 0; i<robots.size();i++)
        delete robots[i];
    for (unsigned int i = 0; i<objets.size();i++)
        delete objets[i];
}

void Table::update(int dt)
{
    //exit(0);
	this->dt = dt;
	for(unsigned int i=0; i < robots.size(); i++)
	{
		robots[i]->updateForces(dt);
       // robots[i]->interact(elements);

        std::cout << Odometrie::odometrie->getPos().getPosition().getX() << " " <<  Odometrie::odometrie->getPos().getPosition().getY() << std::endl;
	}
    if (dt) {
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
    p.setWindow(QRect(0,-tableHeight,tableWidth,tableHeight));
	p.setWorldMatrixEnabled(true);

	// dessine la table
	tableGraphics.draw(&p);


    for (unsigned int i=0; i < objets.size(); i++)
        objets[i]->paint(p);

    for(unsigned int i=0; i < 20; i++)
        p_bougies[i].draw(p);

    for(unsigned int i=0; i < 20; i++)
        p_balles[i].draw(p);

	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->paint(p,dt);

	dt = 0;

    // Dessin d'un trajet
/*	PositionPlusAngle** path = CommandGoTo::path();
    	p.setPen(QColor(Qt::black));
	if (path)
	{
		for(unsigned int i=0; i+1 < PATH_LENGTH; i++)
		p.drawLine(path[i]->position.x, -path[i]->position.y, path[i+1]->position.x, -path[i+1]->position.y);
	CommandGoTo::deletePath(path);
	}
*/
    evt->ignore();
}

void Table::keyPressEvent(QKeyEvent* evt, bool press)
{
	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->keyPressEvent(evt, press);


    Sensors::getSensors()->keyPressEvent(evt,press);
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
    return robots[0];
}
