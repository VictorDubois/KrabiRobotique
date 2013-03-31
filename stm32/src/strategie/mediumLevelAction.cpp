#include "mediumLevelAction.h"

MediumLevelAction::MediumLevelAction(int posX, int posY, vector<LowLevelAction*> actions)
{
    this->robotPosition[0] = posX;
    this->robotPosition[1] = posY;
    this->actionsToDo = actions;
    this->status = 0;
}
MediumLevelAction::~MediumLevelAction()
{
}

int MediumLevelAction::update() {

}

void MediumLevelAction::getRobotPosition(int* ptr) {
	*ptr = this->robotPosition[0];
    *(ptr+1) = this->robotPosition[1];
}

void MediumLevelAction::setRobotPosition(int* robotPosition) {
	this->robotPosition[0] = *robotPosition;
	this->robotPosition[1] = *(robotPosition+1);
}

int MediumLevelAction::getStatus() {
	return this->status;
}

void MediumLevelAction::setStatus(int status) {
	this->status = status;
}
