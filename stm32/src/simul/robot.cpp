#include "simul/robot.h"
#include "element.h"
#include "pince.h"
#include <cmath>


#include "odometrie.h"
#include "asservissement.h"
#include "strategie.h"
#include <iostream>

//Odometrie class implementation for the simulation
//Yes, it's ugly ! it should not be in this file.
//But in a separate file
Odometrie::Odometrie(Robot* robot)
{
	this->robot = robot;
}

PositionPlusAngle Odometrie::getPos()
{
	return robot->pos;
}

Distance Odometrie::getVitesseLineaire()
{
	return robot->deriv.position.getNorme();
}

Angle Odometrie::getVitesseAngulaire()
{
	return robot->deriv.angle;
}

void Odometrie::setPos(PositionPlusAngle p)
{
	robot->pos = p;
}


Robot::Robot(b2World & world) : world(world), olds(10000)
{


	manual = false;
	elem = NULL;
	joint = NULL;
	level = 0;

	odometrie = new Odometrie(this);
	asservissement = new Asservissement(odometrie);
	strategie = new Strategie(true, odometrie, new Pince(this));
	asservissement->strategie = strategie;

	pos = odometrie->getPos();
	deriv.position.x = 0;
	deriv.position.y = 0;
	deriv.angle = 0;


	b2BodyDef bodyDef;
#ifndef BOX2D_2_0_1
	bodyDef.type = b2_dynamicBody;
#endif
	bodyDef.position.Set(pos.position.x/100., pos.position.y/100.);
	bodyDef.angle = pos.angle;
	
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

	box.SetAsBox(1.15,1.795, b2Vec2(-1.49+1.04,0),0);
	body->CreateFixture(&fixture);

#ifdef BOX2D_2_0_1
	b2Vec2* v = box.vertices;
	box.vertexCount = 4;
#else
	b2Vec2 v[4];
#endif
	int inc = 0;
	v[inc++].Set(-.97+1.04,1.07);
	v[inc++].Set(.60+1.04,1.07);
	v[inc++].Set(0+1.04,1.795);
	v[inc++].Set(-0.97+1.04,1.795);
#ifndef BOX2D_2_0_1
	box.Set(v, 4);
#endif
	body->CreateFixture(&fixture);

	inc = 0;
	v[inc++].Set(-0.97+1.04,-1.795);
	v[inc++].Set(0+1.04,-1.795);
	v[inc++].Set(.60+1.04,-1.07);
	v[inc++].Set(-.97+1.04,-1.07);
#ifndef BOX2D_2_0_1
	box.Set(v, 4);
#endif
	body->CreateFixture(&fixture);

#ifdef BOX2D_2_0_1
	body->SetMassFromShapes();
#endif

	//Little hack so that linear and angular speed of the object
	//are those of the local coord (0,0) of the robot.
	//We don't really care of the mass center accuracy.
	b2MassData md;
	body->GetMassData(&md);
	md.center = b2Vec2(0,0);
	body->SetMassData(&md);
}

void Robot::updateForces(int dt)
{
	if(dt == 0)
		return;

	Position impulse;
	impulse.x = (deriv.position.x*(float)cos(pos.angle) - deriv.position.y*(float)sin(pos.angle));
	impulse.y = (deriv.position.x*(float)sin(pos.angle) + deriv.position.y*(float)cos(pos.angle));

	float32 rdt = 1000./(float)dt;

	b2Vec2 bvelocity = 0.01*rdt*b2Vec2(impulse.x,impulse.y);
	float bangular = deriv.angle*rdt;
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

		deriv.position.x = derx*cos(pos.angle) + dery*sin(pos.angle);
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
			deriv.position.x = asservissement->getLinearSpeed();
			deriv.position.y = 0;
			deriv.angle = asservissement->getAngularSpeed();
		}
	}

	p.setWorldTransform(QTransform().translate(pos.position.x,-pos.position.y).rotateRadians(-pos.angle));


	p.setPen(QColor(Qt::black));
	p.setBrush(QBrush(QColor(90,90,90)));
	p.setOpacity(.3);

	QPoint po[10];
	int inc = 0;
	po[inc++] = QPoint(0+104,-179.5);
	po[inc++] = QPoint(-262+104,-179.5);
	po[inc++] = QPoint(-262+104,179.5);
	po[inc++] = QPoint(0+104,179.5);
	po[inc++] = QPoint(60+104,114.5);
	po[inc++] = QPoint(60+104,-114.5);
	p.drawConvexPolygon(po, 6);

	p.drawChord(-103/2 + 104, -107, 2*103, 215, 16*90, 16*180);
	//p.drawRect(-268, -179.5, 268, 359);
	//drawTriangle(p, 0, 0,  65, 0,  60, 0);
	p.setOpacity(1);

	p.setPen(QColor(Qt::red));
	p.drawLine(0,0,pos.position.x,0);
	p.drawLine(0,100*pos.angle,0,0);
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

	if(evt && press && evt->text() == "i" && !evt->isAutoRepeat())
		makeJoint();

	if(evt && press && evt->text() == "u" && !evt->isAutoRepeat() && elem)
	{
		level = (level != 100) ? 100 : 0;
#ifdef BOX2D_2_0_1
#define b2Filter b2FilterData
#define GetFixtureList GetShapeList
#endif
		b2Filter filter;
		if(level == 100)
		{
			filter.categoryBits = 0x4;
			filter.maskBits = 0x3;
		}
		else
		{
			filter.maskBits = 0x3;
			filter.categoryBits = 0x1;
			if(elem->type != Element::Pawn)
			{
				filter.categoryBits = 0x2;
				filter.maskBits |= 0x4;
			}
		}
		elem->body->GetFixtureList()[0].SetFilterData(filter);
	}


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

void Robot::makeJoint()
{
	if(!elem)
		return;

	if(joint)
	{
		world.DestroyJoint(joint);
		joint = NULL;
		level = 0;
	}
	else
	{
		b2WeldJointDef jointDef;
		jointDef.bodyA = body;
		jointDef.bodyB = elem->body;
		jointDef.localAnchorA = body->GetLocalPoint(elem->body->GetPosition());
		joint = world.CreateJoint(&jointDef);
	}
}

void Robot::interact(std::vector<class Element*> &elements)
{
	Element* ne = NULL;

	for(unsigned int i=0; i < elements.size(); i++)
	{
		Element* e = elements[i];
		float d = (e->body->GetPosition() - body->GetWorldPoint(b2Vec2(1.64, 0.))).LengthSquared();
		if(d < 0.01 && (e != elem || !ne))
			ne = e;

		strategie->updateElement(i, *(elements[i]));
	}

	if(elem && elem == ne)
		return;

	if(level == 100 && elem && ne)
	{
		for(std::vector<Element*>::iterator iter = elements.begin(); iter != elements.end(); iter++)
			if(*iter == ne)
			{
				elements.erase(iter);
				break;
			}
		//std::remove(elements.begin(), elements.end(), ne);
		world.DestroyBody(ne->body);
		elem->multiplier += ne->multiplier;
		delete ne;
	}
	else
		elem = ne;
}

