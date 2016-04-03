#include "dune.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Dune::Dune(){}

Dune::Dune(Position goalPosition, Benne* benne):MediumLevelAction(goalPosition)
{
    goalPosition = this->goalPosition;
    benne_locale = benne;
}

Dune::~Dune(){}

Etape::EtapeType Dune::getType()
{
    return Etape::DUNE;
}

int Dune::update()
{

    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "Dune";
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
        qDebug() << "Etape dune finie";

#endif
        benne_locale->setBenneFull();
        status = -1;
    }

    return status;
}
