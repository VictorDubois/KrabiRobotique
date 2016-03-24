#include "cubeDebut.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

CubeDebut::CubeDebut(){}

CubeDebut::CubeDebut(Position goalPosition, Position wa_position):MediumLevelAction(goalPosition)
{
    goalPosition = this->goalPosition;
    position_depart = wa_position;
}

CubeDebut::~CubeDebut(){}

Etape::EtapeType CubeDebut::getType()
{
    return Etape::CUBE_DEBUT;
}

int CubeDebut::update()
{

    if (status == 0) //Début
    {
        StrategieV2::setCurrentGoal(this->getGoalPosition(), false, VITESSE_LINEAIRE_MAX, -100.0, 100.f);
#ifndef ROBOTHW
        qDebug() << "Poussage des cubes devant la zone de depart";
#endif
     status++;
    }

    else if (status == 1) {
        if (Command::isNear(this->getGoalPosition(), 100.0f)) // le second paramètre est la distance a l'objectif
        {
            // après avoir poussé les cubes on revient en marche arrière
            StrategieV2::setCurrentGoal(position_depart, true, VITESSE_LINEAIRE_MAX, -100.0, 10.f);
#ifndef ROBOTHW
        qDebug() << "On revient au bercail";
#endif
            status++;
        }
    }

    else if (status == 2) {

        if (Command::isNear(position_depart, 10.0f)) // le second paramètre est la distance a l'objectif
        {
#ifndef ROBOTHW
        qDebug() << "On est revenu au bercail";
#endif
            status++;
        }
    }

    else if (status == 3) {
#ifndef ROBOTHW
        qDebug() << "Etape poussage des cubes finie";
#endif
        status = -1;
    }

    return status;
}
