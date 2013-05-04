#include "mediumLevelAction.h"

MediumLevelAction::MediumLevelAction(Position goalPos) : goalPosition(goalPos)
{
    status = 0;
}

MediumLevelAction::~MediumLevelAction()
{
    //dtor
}

Position MediumLevelAction::getGoalPosition()
{
    return goalPosition;
}

bool MediumLevelAction::getGoBack()
{
    return goBack;
}

void MediumLevelAction::collisionAvoided()
{
    status = 0; // reinitialize the status if function not overloaded
}
