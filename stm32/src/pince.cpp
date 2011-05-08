

#include "pince.h"
#include"servo.h"


#ifdef ROBOTHW  // vrai robot

Pince::Pince(Servo serv1, Servo serv2) : serv1(1),serv2(2)
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



#else //simulation

#include "simul/element.h"
#include "simul/robot.h"

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
    return robot->level;
}
void Pince::setLevel(unsigned int h)
{
	robot->level = h;
};

void Pince::lacherElem()
{
	if(robot->joint)
   	    robot->makeJoint();
};

#endif
