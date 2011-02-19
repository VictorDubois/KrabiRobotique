#include "simul/element.h"
#include "simul/robot.h"

#include "pince.h"
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

