#include "simul/table.h"
#include "simul/robot.h"
#include "element.h"

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
//	world(b2Vec2(0.f,0.f), false)
	world(b2Vec2(0.f,0.f))
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

	box.SetAsBox(1,20, b2Vec2(-1,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(1,20, b2Vec2(31,0),0);
	tableBody->CreateFixture(&fixture);

	box.SetAsBox(30.,1., b2Vec2(0,21),0);
	tableBody->CreateFixture(&fixture);

	//Starting zones borders
	box.SetAsBox(4.00,.11, b2Vec2(0.,5.1), 0.);
	tableBody->CreateFixture(&fixture);
	box.SetAsBox(4.00,.11, b2Vec2(30.,5.1), 0.);
	tableBody->CreateFixture(&fixture);

	//Blocked zones
    box.SetAsBox(1.25,1.25, b2Vec2(11.,10.), 0.); //Totem rouge
	tableBody->CreateFixture(&fixture);
    box.SetAsBox(1.25,1.25, b2Vec2(19.,10.), 0.); //Totem violet
	tableBody->CreateFixture(&fixture);
    box.SetAsBox(0.2,0.2, b2Vec2(15.,10.), 0.); //Arbre TODO : à transformer en cercle
	tableBody->CreateFixture(&fixture);


	//Boat
    box.SetAsBox(0.11,3.75, b2Vec2(3.24,16.3), 0.0666); //Red Boat
	tableBody->CreateFixture(&fixture);
    box.SetAsBox(0.11,3.75, b2Vec2(26.76,16.3), 6.216); //Violet Boat
	tableBody->CreateFixture(&fixture);

/*	box.SetAsBox(3.50,1.20, b2Vec2(8,21), 0.);
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
	//int l1 = rand() % 20;
	int l1 =15;
	int l2 = rand() % 20;
	//int l2 = 20;
	int r1 = rand() % 20;

	addCard(l1, 1);
	addCard(l2, 2);
	addCard(l2, 4);
	addCard(l1, 5);
	addCard(r1, -1);
	addCard(r1, -2);
	elements.push_back(new Element(world,getCase(3,3),Element::Pawn)); //Central element
*/
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


	//Mer
	p.fillRect(0,0,3000,-2000,QColor(39,129,187)); // Blue
	//Starting zones
	p.fillRect(0,0,500,-500,QColor(160,0,28)); //Red
	p.fillRect(2500,0,500,-500,QColor(133,61,125)); //Violet
	//Boat
	p.setBrush(QBrush(QColor(119,76,59))); //Brown
	p.setPen(QBrush(QColor(119,76,59)));

	static const QPointF redBoat[4] = {QPointF(0, -500),QPointF(0, -2000), QPointF(325, -2000), QPointF(400, -500) };
	p.drawPolygon(redBoat, 4, Qt::OddEvenFill);

	static const QPointF violetBoat[4] = {QPointF(2600, -500),QPointF(2675, -2000), QPointF(3000, -2000), QPointF(3000, -500) };
	p.drawPolygon(violetBoat, 4, Qt::OddEvenFill);

	//Circle of the map
	p.setBrush(QBrush(QColor(242,191,0))); // Jaune
	p.setPen(QBrush(QColor(242,191,0)));
	float diameter = 800;
	p.drawEllipse(QRectF(1500 -diameter / 2.0, -diameter / 2.0, diameter, diameter));

	p.setBrush(QBrush(QColor(75,155,62))); // Vert
	p.setPen(QBrush(QColor(75,155,62)));
	diameter = 600;
	p.drawEllipse(QRectF(1500 -diameter / 2.0, -diameter / 2.0, diameter, diameter));

	//Island
	p.setBrush(QBrush(QColor(242,191,0))); // Jaune
	p.setPen(QBrush(QColor(242,191,0)));
	diameter = 600;
	p.drawEllipse(QRectF(1100 -diameter / 2.0, -1000 -diameter / 2.0, diameter, diameter));
	p.drawEllipse(QRectF(1900 -diameter / 2.0, -1000 -diameter / 2.0, diameter, diameter));
	p.fillRect(1100,-800,800,-400,QColor(242,191,0));
	p.setBrush(QBrush(QColor(39,129,187))); // Blue
        p.setPen(QBrush(QColor(39,129,187)));
	diameter = 237*2;
	p.drawEllipse(QRectF(1500 -diameter / 2.0, -1358 -diameter / 2.0, diameter, diameter));
	p.drawEllipse(QRectF(1500 -diameter / 2.0, -1000+358 -diameter / 2.0, diameter, diameter));

	p.setBrush(QBrush(QColor(75,155,62))); // Vert
	p.setPen(QBrush(QColor(75,155,62)));
	diameter = 150; // arbre central
	p.drawEllipse(QRectF(1500 -diameter / 2.0, -1000 -diameter / 2.0, diameter, diameter));

	diameter = 400; // autour des totems
	p.drawEllipse(QRectF(1100 -diameter / 2.0, -1000 -diameter / 2.0, diameter, diameter));
	p.drawEllipse(QRectF(1900 -diameter / 2.0, -1000 -diameter / 2.0, diameter, diameter));

	//Lignes noires de suivie
	p.fillRect(500,-450,150,-20,Qt::black);
	p.fillRect(630,-450,20,-1550,Qt::black);

	p.fillRect(2350,-450,150,-20,Qt::black);
	p.fillRect(2350,-450,20,-1550,Qt::black);

	//Totem
	p.fillRect(975,-875,250,-250,QColor(119,76,59));
	p.fillRect(1775,-875,250,-250,QColor(119,76,59));

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
	unsigned int k = n % 5;
	unsigned int q = n % 3;
	if(q >= k)
		q++;

	if(column > 0)
	{
		//elements.push_back(new Element(world,getCase(column,k+1),Element::Pawn));
		//elements.push_back(new Element(world,getCase(column,q+1),Element::Pawn));
		elements.push_back(new Element(world,getCase(column,4),Element::Pawn));
		elements.push_back(new Element(world,getCase(column,5),Element::Pawn));
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

