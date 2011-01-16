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
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.position.x.getValueInMillimeters()/100., pos.position.y.getValueInMillimeters()/100.);
	bodyDef.angle = pos.angle.getValueInRadian();
	
	body = world.CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(1.,1., b2Vec2(1,1),0);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &box;
	fixtureDef.density = 10.0f;
	fixtureDef.friction = 0.f;
	body->CreateFixture(&fixtureDef);
}

void Robot::updateForces(int dt)
{
	if(dt == 0)
		return;

	Position impulse;
	impulse.x = (deriv.position.x*cos(pos.angle.getValueInRadian()) - deriv.position.y*sin(pos.angle.getValueInRadian()));
	impulse.y = (deriv.position.x*sin(pos.angle.getValueInRadian()) + deriv.position.y*cos(pos.angle.getValueInRadian()));

	float32 rdt = 1000./(float)dt;

	b2Vec2 bimpulse = 0.01*rdt*b2Vec2(impulse.x.getValueInMillimeters(),impulse.y.getValueInMillimeters());
	float bangular = deriv.angle.getValueInRadian()*rdt;
	//body->ApplyForce(10*body->GetMass()*(bimpulse - body->GetLinearVelocity()), body->GetWorldCenter());
	//body->ApplyTorque((bangular - body->GetAngularVelocity())*body->GetInertia());
	body->SetLinearVelocity(bimpulse);
	body->SetAngularVelocity(bangular);

}


void Robot::paint(QPainter &p, int dt)
{
	if(dt)
	{
		pos.position.x = 100*body->GetWorldCenter().x;
		pos.position.y = 100*body->GetWorldCenter().y;
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
			deriv.position.x = deriv.position.x* 0.97;
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

	p.setWorldTransform(QTransform().translate(pos.position.x.getValueInMillimeters(),pos.position.y.getValueInMillimeters()).rotateRadians(pos.angle.getValueInRadian()));


	p.setPen(QColor(Qt::black));
	p.setBrush(QBrush(QColor(90,90,90)));
	p.setOpacity(.3);
	p.drawRect(-100, -100, 200, 200);
	p.setOpacity(1);

	p.setPen(QColor(Qt::red));
	p.drawLine(0,0,pos.position.x.getValueInMillimeters(),0);
	p.drawLine(0,100*pos.angle.getValueInRadian(),0,0);
	p.setWorldTransform(QTransform());


	p.setPen(QColor(Qt::green));
	for(unsigned int i=0; i+1 < olds.size(); i++)
		p.drawLine(olds[i].position.x.getValueInMillimeters(), olds[i].position.y.getValueInMillimeters(), olds[i+1].position.x.getValueInMillimeters(), olds[i+1].position.y.getValueInMillimeters());	
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
			deriv.angle += ainc;
		IF_KEYSWITCH(droite,evt->key() == Qt::Key_Left)
			deriv.angle -= ainc;
	}
}

