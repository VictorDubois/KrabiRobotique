#include "simul/element.h"
#include "simul/robot.h"

#include "pince.h"
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

