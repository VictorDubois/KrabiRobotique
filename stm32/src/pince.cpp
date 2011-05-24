
#include "pince.h"

#ifdef ROBOTHW

Pince::Pince(Servo serv1, Servo serv2) : serv1(serv1), serv2(serv2)
{
}

void Pince::pivote(Angle angle)
{
    serv1.goToAngle(angle);
    serv2.goToAngle(-angle);
}

Pince::~Pince()
{
}

#else
#include "simul/element.h"
#include "simul/robot.h"

#include<iostream>
using namespace std;


Pince::Pince(Robot* robot)
{
	this->robot = robot;
};

void Pince::serrerElem()
{
	if(!robot->joint)
   	    robot->makeJoint();
};
unsigned int Pince::getLevel()
{
    cout<<robot->level<<endl;
    return robot->level;
}
void Pince::setLevel()
{
	robot->setLevel();
};

void Pince::lacherElem()
{
	if(robot->joint)
   	    robot->makeJoint();
};

#endif //ROBOTHW

