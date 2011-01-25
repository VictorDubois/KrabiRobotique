#include "simul/robot.h"
#include <cmath>


#include "odometrie.h"
#include "asservissement.h"
#include "strategie.h"
#include <iostream>

class OdoRobot : public Odometrie
{
private:
	Robot* robot;

public:
	OdoRobot(Robot* robot)
	{
		this->robot = robot;
	}

	PositionPlusAngle getPos()
	{
		return robot->pos;
	}

	Distance getVitesseLineaire()
	{
		return robot->deriv.position.getNorme();
	}

	Angle getVitesseAngulaire()
	{
		return robot->deriv.angle;
	}

	void setPos(PositionPlusAngle p)
	{
		robot->pos = p;
	}
};


Robot::Robot(b2World & world) : olds(10000)
{

	deriv.position.x = 0;
	deriv.position.y = 0;
	deriv.angle = 0;

	manual = false;

	odometrie = new OdoRobot(this);
	asservissement = new Asservissement(odometrie);
	strategie = new Strategie(true, asservissement);

	pos.position.x=1000.;
	pos.position.y=500.;
	pos.angle=0;

	asservissement->strategie = strategie;

	b2BodyDef bodyDef;
#ifndef BOX2D_2_0_1
	bodyDef.type = b2_dynamicBody;
#endif
	bodyDef.position.Set(pos.position.x/100., pos.position.y/100.);
	bodyDef.angle = pos.angle.getValueInRadian();
	
	body = world.CreateBody(&bodyDef);

#ifdef BOX2D_2_0_1
	b2PolygonDef box;
	b2PolygonDef &fixture = box;
#define CreateFixture CreateShape
#else
	b2PolygonShape box;
	b2FixtureDef fixture;
	fixture.shape = &box;
#endif
	fixture.density = 10.0f;
	fixture.friction = 1.0f;

	box.SetAsBox(1.15,1.795, b2Vec2(-1.49,0),0);
	body->CreateFixture(&fixture);

	box.m_vertexCount = 4;
	int inc = 0;
	box.m_vertices[inc++].Set(-.97,1.07);
	box.m_vertices[inc++].Set(.60,1.07);
	box.m_vertices[inc++].Set(0,1.795);
	box.m_vertices[inc++].Set(-0.97,1.795);
	body->CreateFixture(&fixture);

	inc = 0;
	box.m_vertices[inc++].Set(-0.97,-1.795);
	box.m_vertices[inc++].Set(0,-1.795);
	box.m_vertices[inc++].Set(.60,-1.07);
	box.m_vertices[inc++].Set(-.97,-1.07);
	body->CreateFixture(&fixture);
	//setTriangle(box, 0, 0, 


#ifdef BOX2D_2_0_1
	body->SetMassFromShapes();
#endif
}

void Robot::updateForces(int dt)
{
	if(dt == 0)
		return;

	Position impulse;
	impulse.x = (deriv.position.x*(float)cos(pos.angle.getValueInRadian()) - deriv.position.y*(float)sin(pos.angle.getValueInRadian()));
	impulse.y = (deriv.position.x*(float)sin(pos.angle.getValueInRadian()) + deriv.position.y*(float)cos(pos.angle.getValueInRadian()));

	float32 rdt = 1000./(float)dt;

	b2Vec2 bvelocity = 0.01*rdt*b2Vec2(impulse.x,impulse.y);
	float bangular = deriv.angle.getValueInRadian()*rdt;
	//body->ApplyForce(10*body->GetMass()*(bimpulse - body->GetLinearVelocity()), body->GetWorldCenter());
	//body->ApplyTorque((bangular - body->GetAngularVelocity())*body->GetInertia());
	
	body->SetLinearVelocity(bvelocity);
	body->SetAngularVelocity(bangular);

}


void Robot::paint(QPainter &p, int dt)
{
	if(dt)
	{
		pos.position.x = 100*body->GetPosition().x;
		pos.position.y = 100*body->GetPosition().y;
		pos.angle = body->GetAngle();

		float rdt = (float)dt/1000.;
		deriv.angle = body->GetAngularVelocity()*rdt;
		float derx = 100*body->GetLinearVelocity().x*rdt;
		float dery = 100*body->GetLinearVelocity().y*rdt;

		deriv.position.x = derx*cos(pos.angle.getValueInRadian()) + dery*sin(pos.angle.getValueInRadian());
		deriv.position.y = 0;

		olds.push_back(pos);
		if(manual)
		{
			keyPressEvent(NULL,false);
			deriv.position.x = deriv.position.x* 0.97f;
			deriv.angle = deriv.angle * 0.9;
		}
		else
		{
			Asservissement::asservissement->update();
			deriv.position.x = asservissement->vitesse_lineaire_a_atteindre;
			deriv.position.y = 0;
			deriv.angle = asservissement->vitesse_angulaire_a_atteindre;
		}
	}

	p.setWorldTransform(QTransform().translate(pos.position.x,-pos.position.y).rotateRadians(-pos.angle.getValueInRadian()));


	p.setPen(QColor(Qt::black));
	p.setBrush(QBrush(QColor(90,90,90)));
	p.setOpacity(.3);

	QPoint po[10];
	int inc = 0;
	po[inc++] = QPoint(0,-179.5);
	po[inc++] = QPoint(-262,-179.5);
	po[inc++] = QPoint(-262,179.5);
	po[inc++] = QPoint(0,179.5);
	po[inc++] = QPoint(60,114.5);
	po[inc++] = QPoint(60,-114.5);
	p.drawConvexPolygon(po, 6);

	p.drawChord(-103/2, -107, 2*103, 215, 16*90, 16*180);
	//p.drawRect(-268, -179.5, 268, 359);
	//drawTriangle(p, 0, 0,  65, 0,  60, 0);
	p.setOpacity(1);

	p.setPen(QColor(Qt::red));
	p.drawLine(0,0,pos.position.x,0);
	p.drawLine(0,100*pos.angle.getValueInRadian(),0,0);
	p.setWorldTransform(QTransform());


	p.setPen(QColor(Qt::green));
	for(unsigned int i=0; i+1 < olds.size(); i++)
		p.drawLine(olds[i].position.x, -olds[i].position.y, olds[i+1].position.x, -olds[i+1].position.y);	
}

#define IF_KEYSWITCH(n,a) \
static bool n=false; \
if(evt) n= a ? press : n; if(n)

void Robot::keyPressEvent(QKeyEvent* evt, bool press)
{
	if(evt && press && evt->text() == "e" && !evt->isAutoRepeat())
		manual = !manual;

	if(manual)
	{
		float dinc = .5;
		float ainc = 0.005;

		IF_KEYSWITCH(avant,evt->key() == Qt::Key_Up)
			deriv.position.x += dinc;
		IF_KEYSWITCH(arriere,evt->key() == Qt::Key_Down)
			deriv.position.x -= dinc;
		IF_KEYSWITCH(gauche,evt->key() == Qt::Key_Right)
			deriv.angle -= ainc;
		IF_KEYSWITCH(droite,evt->key() == Qt::Key_Left)
			deriv.angle += ainc;
	}
}
