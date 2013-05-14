#include "mediumLevelAction.h"
#include "strategieV2.h"

MediumLevelAction::MediumLevelAction(Position goalPos) 
{
    goalPosition = goalPos; //(StrategieV2::getIsBlue() ? goalPos : Position(3000,0)-goalPos);
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

void MediumLevelAction::setGoBack(bool val)
{
    goBack = val;
}
