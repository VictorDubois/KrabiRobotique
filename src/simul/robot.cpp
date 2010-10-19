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

	odometrie = new OdoRobot(this);
	asservissement = new Asservissement(odometrie);
	strategie = new Strategie(true, asservissement);
	asservissement->strategie = strategie;
}

void Robot::paint(QPainter &p, int dt)
{
	Asservissement::asservissement->update();
	deriv.position.x = asservissement->vitesse_lineaire_a_atteindre;
	deriv.angle = asservissement->vitesse_angulaire_a_atteindre;

	p.setWorldTransform(QTransform().translate(pos.position.x.getValueInMillimeters(),pos.position.y.getValueInMillimeters()).rotateRadians(pos.angle.getValueInRadian()));
	p.setPen(QColor(Qt::black));
	p.drawRect(-100, -100, 200, 200);
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
