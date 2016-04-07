#include "zoneConstruction.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"
#include "krabi2016.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

ZoneConstruction::ZoneConstruction(){}

ZoneConstruction::ZoneConstruction(Position goalPosition, Benne* benne):MediumLevelAction(goalPosition)
{
    goalPosition = this->goalPosition;
    benne_locale = benne;
}

ZoneConstruction::~ZoneConstruction(){}

Etape::EtapeType ZoneConstruction::getType()
{
    return Etape::ZONE_CONSTRUCTION;
}

int ZoneConstruction::update()
{

    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "Zone Construction";
#endif
        //StrategieV2::setCurrentGoal(this->getGoalPosition(), false, VITESSE_LINEAIRE_MAX, -100.0, 200.f);

        status++;
    }

    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(this->getGoalPosition(), false, VITESSE_LINEAIRE_MAX, -100.0, 200.f);
        status++;
    }

    else if (status == 2) {
        if (Command::isNear(this->getGoalPosition(), 100.0f)) // le second paramètre est la distance a l'objectif
        {
            StrategieV2::stop();
            StrategieV2::lookAt(this->getGoalPosition());
            status++;
        }

    }

    else if (status == 3) {
#ifndef ROBOTHW
        qDebug() << "Etape zone de construction finie ; benne vide";
#endif
        benne_locale->setBenneEmpty();
        status = -1;
    }

    return status;
}
