#include "cabine.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Cabine::Cabine(){}

Cabine::Cabine(Position goalPosition, Position wd_position):MediumLevelAction(goalPosition)
{
    goalPosition = this->goalPosition;
    position_depart = wd_position;
}

Cabine::~Cabine(){}

Etape::EtapeType Cabine::getType()
{
    return Etape::CABINE;
}

int Cabine::update()
{

    if (status == 0) //Début
    {
        StrategieV2::setCurrentGoal(this->getGoalPosition(), false, VITESSE_LINEAIRE_MAX, -100.0, 200.f);
#ifndef ROBOTHW
        qDebug() << "On se prepare a pousser une porte";
#endif
     status++;
    }

    else if (status == 1) {
        if (Command::isNear(this->getGoalPosition(), 200.0f)) // le second paramètre est la distance a l'objectif
        {
            // après avoir poussé les cubes on revient en marche arrière
            StrategieV2::setCurrentGoal(position_depart, true, VITESSE_LINEAIRE_MAX, -100.0, 10.f);
#ifndef ROBOTHW
        qDebug() << "On revient en marche arriere au point ou on prend son elan";
#endif
            status++;
        }
    }

    else if (status == 2) {

        if (Command::isNear(position_depart, 10.0f)) // le second paramètre est la distance a l'objectif
        {
#ifndef ROBOTHW
        qDebug() << "On est revenu au point ou on prend son elan";
#endif
            status++;
        }
    }

    else if (status == 3) {
#ifndef ROBOTHW
        qDebug() << "Etape fermeture de cabine finie";
#endif
        status = -1;
    }

    return status;
}
