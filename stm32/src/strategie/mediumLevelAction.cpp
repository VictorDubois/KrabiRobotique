#include "mediumLevelAction.h"
#include "strategieV2.h"

#include <QDebug>

MediumLevelAction::MediumLevelAction(Position goalPos, bool goBack) : goalPosition(goalPos), status(0), goBack(goBack)
{
    //(StrategieV2::getIsBlue() ? goalPos : Position(3000,0)-goalPos);
#ifndef ROBOTHW
    qDebug() << this->goBack;
#endif
}

MediumLevelAction::~MediumLevelAction()
{}

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

void MediumLevelAction::reset()
{}

Etape::EtapeType MediumLevelAction::getType()
{
    return Etape::POINT_PASSAGE;
}

#ifndef ROBOTHW
void MediumLevelAction::paint(QPainter* p)
{}
#endif

void MediumLevelAction::updateTime(int millisecondesRestantes)
{
    this->millisecondesRestantes = millisecondesRestantes;
}
