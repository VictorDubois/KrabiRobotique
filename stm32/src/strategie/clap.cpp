#include "clap.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"
#include "brasLateraux.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Clap::Clap(){}

Clap::Clap(Position positionDepart, Position positionArrivee):MediumLevelAction(positionDepart)
{
    this->positionArrivee = positionArrivee;
    this->goBack = false;
}

Clap::~Clap(){}

Etape::EtapeType Clap::getType()
{
    return Etape::CLAP;
}

int Clap::update()
{

    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "clap";
#endif
        status++;
    }

    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(goalPosition, goBack);
        status++;
    }

    else if (status == 2)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(positionArrivee);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(positionArrivee))
        {
            //ouvrir le bras

            if ((goalPosition.getX()-positionArrivee.getX())>0)
                BrasLateraux::getRight()->expand();
            else
                BrasLateraux::getLeft()->expand();
            status++;
        }
    }

    else if ((status <= 53) && (status > -1 ))    //On attend que le bras du robot s'ouvre : 50ms par incrémentation du status
    {
        status++;
    }

    else if (status == 54)
    {
        StrategieV2::setCurrentGoal(positionArrivee, goBack);
        status++;
    }

    else if (status == 55)
    {
        if (Command::isNear(positionArrivee))
        {
            //fermer bras

            if ((goalPosition.getX()-positionArrivee.getX())>0)
                BrasLateraux::getLeft()->collapse();
            else
                BrasLateraux::getRight()->collapse();
            status++;
        }
    }

    else if ((status <= 105) && (status > -1))
    {
        status++;
    }

    else if (status == 106){
        status = -1;
#ifndef ROBOTHW
        qDebug() << "Etape clap finie";
#endif
    }

    return status;
}
