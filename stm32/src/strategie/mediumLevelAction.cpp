#include "mediumLevelAction.h"

MediumLevelAction::MediumLevelAction(Position robotPosition, vector<LowLevelAction*> actions)
{
    this->robotPosition = robotPosition;
    this->actionsToDo = actions;
    this->status = 0;
}
MediumLevelAction::~MediumLevelAction()
{
}

int MediumLevelAction::update() {

}

const Position& MediumLevelAction::getRobotPosition()
{
    return this->robotPosition;
}

void MediumLevelAction::setRobotPosition(const Position& position)
{
    this->robotPosition = position;
}

int MediumLevelAction::getStatus() {
	return this->status;
}

void MediumLevelAction::setStatus(int status) {
	this->status = status;
}
