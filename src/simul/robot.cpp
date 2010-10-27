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

	Distance vitesseLineaire()
	{
		return robot->deriv.position.getNorme();
	}

	Angle vitesseAngulaire()
	{
		return robot->deriv.angle;
	}

	void setPos(PositionPlusAngle p)
	{
		robot->pos = p;
	}
};


Robot::Robot() : olds(10000)
{
	pos.position.x=1000;
	pos.position.y=500;
	pos.angle=0;

	deriv.position.x = 0;
	deriv.position.y = 0;
	deriv.angle = 0;

	manual = false;

	odometrie = new OdoRobot(this);
	asservissement = new Asservissement(odometrie);
	strategie = new Strategie(true, asservissement);
	asservissement->strategie = strategie;
}

void Robot::paint(QPainter &p, int dt)
{
	if(manual)
	{
		keyPressEvent(NULL,false);
		deriv.position.x = deriv.position.x* 0.99;
		deriv.angle = deriv.angle * 0.9;
	}
	else
	{
		Asservissement::asservissement->update();
		deriv.position.x = asservissement->vitesse_lineaire_a_atteindre;
		deriv.angle = asservissement->vitesse_angulaire_a_atteindre;
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

	if(dt)
	{
		olds.push_back(pos);
		pos.position.x += (deriv.position.x*cos(pos.angle.getValueInRadian()) - deriv.position.y*sin(pos.angle.getValueInRadian()));
		pos.position.y += (deriv.position.x*sin(pos.angle.getValueInRadian()) + deriv.position.y*cos(pos.angle.getValueInRadian()));
		pos.angle += deriv.angle;
	}

	p.setPen(QColor(Qt::green));
	for(unsigned int i=0; i < olds.size()-1; i++)
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
		float dinc = 0.1;
		float ainc = 0.003;

		IF_KEYSWITCH(avant,evt->key() == Qt::Key_Up)
			deriv.position.x += dinc;
		IF_KEYSWITCH(arriere,evt->key() == Qt::Key_Down)
			deriv.position.x -= dinc;
		IF_KEYSWITCH(gauche,evt->key() == Qt::Key_Right)
			deriv.angle += ainc;
		IF_KEYSWITCH(droite,evt->key() == Qt::Key_Left)
			deriv.angle -= ainc;
		std::cout << deriv.position.x.getValueInMillimeters() << " & " << deriv.angle.getValueInRadian() << std::endl;
	}
}

