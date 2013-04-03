#include "mediumLevelAction.h"


MediumLevelAction::MediumLevelAction(Position position, int numberOfActions, MEDIUM_LEVEL_ACTION_TYPE type)
{
    this->robotPosition = position;
    this->numberOfActions = numberOfActions;
    this->status = 0;
    this->type = type;
}
MediumLevelAction::~MediumLevelAction()
{
}

int MediumLevelAction::update() {

    return 0;
}

Position MediumLevelAction::getRobotPosition()
{
    return this->robotPosition;
}

void MediumLevelAction::setRobotPosition(Position position)
{
    this->robotPosition = position;
}

int MediumLevelAction::getStatus() {
	return this->status;
}

void MediumLevelAction::setStatus(int status) {
	this->status = status;
}
void MediumLevelAction::addLowLevelAction(LowLevelAction* action)
{
    this->actionsToDo[++numberOfActions] = action;
}
MEDIUM_LEVEL_ACTION_TYPE MediumLevelAction::getType()
{
    return this->type;
}
