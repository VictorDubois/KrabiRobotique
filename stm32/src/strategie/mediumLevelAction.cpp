#include "mediumLevelAction.h"

MediumLevelAction::MediumLevelAction(Position position, int numberOfActions)
{
    this->robotPosition = position;
    this->numberOfActions = numberOfActions;
    this->status = 0;
}
MediumLevelAction::~MediumLevelAction()
{
}

int MediumLevelAction::update() {

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
