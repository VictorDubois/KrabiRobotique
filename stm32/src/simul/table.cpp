#include "simul/table.h"
#include "simul/robot.h"
#include "simul/objet.h"
#include "element.h"
#include "cstdlib"
#include "time.h"

#define PI 3.14159265358979323846264338327950
#include <iostream>
#include <QPainter>
#include "commandGoTo.h"

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
	a.lowerBound.Set(-100,-100);
	a.upperBound.Set(tableWidth+100, tableHeight+100);
	return a;
}

Table::Table(QWidget* parent) :
	QWidget(parent),
#ifdef BOX2D_2_0_1
	world(getWorldAABB(),b2Vec2(0.f,0.f), false)
#else
//	world(b2Vec2(0.f,0.f), false)
	world(b2Vec2(0.f,0.f))
#endif
{
	dt=0;
	setAutoFillBackground(true);

	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);

    //création des robots
	robots.push_back(new Robot(world));

	//création des verres
	// côté bleu
	objets.push_back(new Objet(world, Position(900.,650.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1200.,650.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1050.,900.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1350.,900.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(900.,1150.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1200.,1150.), Objet::glass, 0, QColor(170, 170, 170)));

	// côté rouge
	objets.push_back(new Objet(world, Position(2100.,650.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1800.,650.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1950.,900.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1650.,900.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(2100.,1150.), Objet::glass, 0, QColor(170, 170, 170)));
	objets.push_back(new Objet(world, Position(1800.,1150.), Objet::glass, 0, QColor(170, 170, 170)));




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
	box.SetAsBox(30,1, b2Vec2(0,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(1,20, b2Vec2(-1,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(1,20, b2Vec2(31,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(30,1, b2Vec2(0,22),0);
	tableBody->CreateFixture(&fixture);
    // fin bordures

    // plateaux blancs bords zones départ
    box.SetAsBox(4,1, b2Vec2(0,1),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(30,1),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(0,21),0);
    tableBody->CreateFixture(&fixture);

    box.SetAsBox(4,1, b2Vec2(30,21),0);
    tableBody->CreateFixture(&fixture);

	// gateau
	b2CircleShape circle;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	circle.m_radius = 5.f;
	circle.m_p.Set(15.,21.);
	tableBody->CreateFixture(&fixtureDef);

	// load the graphics of the game.
	tableGraphics.load("tabledata.xml");
	tableGraphics.addYOffset(-tableHeight); // because we want the (0,0) point to be at the bottom left.


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
        p_bougies[i] = Bougie(colors[i], QPointF(1500.f-450.f*cos((7.5+15.f*(float)(i))*PI/180.f), -2100.f+450.f*sin((7.5+15.f*(float)(i))*PI/180.f)), 40.f);
    }
    for (int i = 12; i < 20; i++)
    {
        p_bougies[i] = Bougie(colors[i], QPointF(1500.f-350.f*cos((11.25+22.5f*(float)(i-12))*PI/180.f), -2100.f+350.f*sin((11.25+22.5f*(float)(i-12))*PI/180.f)), 40.f);
    }
    for (int i = 0; i < 12; i++)
    {
        p_balles[i] = Bougie(QColor(255,255,0), QPointF(1500.f-450.f*cos((7.5+15.f*(float)(i))*PI/180.f), -2100.f+450.f*sin((7.5+15.f*(float)(i))*PI/180.f)), 33.f);
    }
    for (int i = 12; i < 20; i++)
    {
        p_balles[i] = Bougie(QColor(255,255,0), QPointF(1500.f-350.f*cos((11.25+22.5f*(float)(i-12))*PI/180.f), -2100.f+350.f*sin((11.25+22.5f*(float)(i-12))*PI/180.f)), 33.f);
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
	this->dt = dt;
	for(unsigned int i=0; i < robots.size(); i++)
	{
		robots[i]->updateForces(dt);
//		robots[i]->interact(elements);
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
