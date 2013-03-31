#include "mediumLevelAction.h"

MediumLevelAction::MediumLevelAction(int posX, int posY, std::vector<LowLevelAction*> actions)
{
    this->robotPosition[0] = posX;  
    this->robotPosition[1] = posY;
    this->actionsToDo = actions;
    this->status = 0;
}
virtual MediumLevelAction::~MediumLevelAction()
{
}

virtual int MediumLevelAction::update() {
	throw "Not yet implemented";
}

int MediumLevelAction::getRobotPosition() {
	return this->robotPosition;
}

void MediumLevelAction::setRobotPosition(int robotPosition) {
	this->robotPosition = robotPosition;
}

int MediumLevelAction::getStatus() {
	return this->status;
}

void MediumLevelAction::setStatus(int status) {
	this->status = status;
}
