#include "simul/table.h"
#include "simul/robot.h"
#include <iostream>
#include <QPainter>

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
	world(b2Vec2(0.f,0.f), false)
#endif
{
	dt=0;
	setAutoFillBackground(true);
	
	QPalette p = palette();
	p.setColor(QPalette::Window,QColor(Qt::darkGray));
	setPalette(p);

	robots.push_back(new Robot(world));

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
	box.SetAsBox(30,1, b2Vec2(0,-1),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(1,21, b2Vec2(-1,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(1,21, b2Vec2(31,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(30.,1., b2Vec2(0,22),0);
	tableBody->CreateFixture(&fixture);

	//Starting zones borders
	box.SetAsBox(4.00,.11, b2Vec2(0.,4.), 0.);
	tableBody->CreateFixture(&fixture);
	box.SetAsBox(4.00,.11, b2Vec2(30.,4.), 0.);
	tableBody->CreateFixture(&fixture);

	//Blocked zones
	box.SetAsBox(3.50,1.20, b2Vec2(8,21), 0.);
	tableBody->CreateFixture(&fixture);
	box.SetAsBox(3.50,1.20, b2Vec2(22,21), 0.);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(.11,0.65, b2Vec2(4.61,19.15), 0.);
	tableBody->CreateFixture(&fixture);
	box.SetAsBox(.11,0.65, b2Vec2(18.61,19.15), 0.);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(.11,0.65, b2Vec2(11.39,19.15), 0.);
	tableBody->CreateFixture(&fixture);
	box.SetAsBox(.11,0.64, b2Vec2(25.39,19.15), 0.);
	tableBody->CreateFixture(&fixture);

	//Init position of elements
	int l1 = rand() % 20; 
	int l2 = rand() % 20; 
	int r1 = rand() % 20; 
	int r2 = rand() % 20; 

	addCard(l1, 1);
	addCard(l2, 2);
	addCard(l2, 4);
	addCard(l1, 5);
	addCard(r1, -1);
	addCard(r2, -2);
	elements.push_back(new Element(world,getCase(3,3),Element::Pawn)); //Central element
}

Table::~Table()
{
}

void Table::update(int dt)
{
	this->dt = dt;
	for(unsigned int i=0; i < robots.size(); i++)
	{
		robots[i]->updateForces(dt);
		robots[i]->interact(elements);
	}

#ifdef BOX2D_2_0_1
	world.Step((float)dt/1000., 10);
#else
	world.Step((float)dt/1000., 10, 10);
	world.ClearForces();
#endif
	for(unsigned int i=0; i < elements.size(); i++)
		elements[i]->updatePos();
	repaint();
}

void Table::paintEvent(QPaintEvent* evt)
{
	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing,true);
	p.setWindow(QRect(0,-tableHeight,tableWidth,tableHeight));
	p.setWorldMatrixEnabled(true);


	for(unsigned int i=0; i<6; i++)
	for(unsigned int j=0; j<6; j++)
		p.fillRect(450+i*350,-j*350,350,-350, ((i+j) & 1) ? Qt::blue : Qt::red);
	//Starting zones
	p.fillRect(0,0,400,-400,Qt::blue);
	p.fillRect(2600,0,400,-400,Qt::red);
	//Green zones
	p.fillRect(0,-400,400,-1700,QColor(0,146,54));
	p.fillRect(2600,-400,400,-1700,QColor(0,146,54));
	//Starting zones borders
	p.fillRect(0,-389,400,-22,Qt::black);
	p.fillRect(2600,-389,400,-22,Qt::black);

	//Blocked zones
	p.fillRect(450,-1980,700,-120,Qt::black);
	p.fillRect(1850,-1980,700,-120,Qt::black);

	p.fillRect(450,-1850,22,-130,Qt::black);
	p.fillRect(1850,-1850,22,-130,Qt::black);

	p.fillRect(1128,-1850,22,-130,Qt::black);
	p.fillRect(2528,-1850,22,-130,Qt::black);

	//Extra-points
	p.setBrush(QBrush(QColor(30,30,30)));
	p.setPen(QBrush(QColor(30,30,30)));

	p.drawEllipse(getCaseCenter(1,1), 50,50);
	p.drawEllipse(getCaseCenter(1,4), 50,50);
	p.drawEllipse(getCaseCenter(4,4), 50,50);
	p.drawEllipse(getCaseCenter(4,1), 50,50);

	p.drawEllipse(getCaseCenter(2,5), 50,50);
	p.drawEllipse(getCaseCenter(3,5), 50,50);

	p.setBrush(QBrush(QColor("yellow")));
	p.setPen(QBrush(QColor("yellow")));

	for(unsigned int i=0; i < elements.size(); i++)
		elements[i]->paint(p);

	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->paint(p,dt);

	dt = 0;
}

void Table::keyPressEvent(QKeyEvent* evt, bool press)
{
	for(unsigned int i=0; i < robots.size(); i++)
		robots[i]->keyPressEvent(evt, press);
}

Position getSideElemCenter(bool right, unsigned int elem)
{
	return Position(right ? 200 : 2800, 1810 - elem*280);
}

void Table::addCard(unsigned int n, int column)
{
	unsigned int k = n % 4;
	unsigned int q = n % 3;
	if(q >= k)
		q++;

	if(column > 0)
	{
		elements.push_back(new Element(world,getCase(column,k+1),Element::Pawn));
		elements.push_back(new Element(world,getCase(column,q+1),Element::Pawn));
	}
	else
	{
		for(unsigned int i=0; i < 5; i++)
		{
			Element::Type t = Element::Pawn;
			if(i == q)
				t = Element::Queen;
			else if(i == k)
				t = Element::King;

			elements.push_back(new Element(world,getSideElemCenter(-column-1, i),t));
		}
	}
}

