#include "gobelet.h"
#include "pinces.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Gobelet::Gobelet(){}

Gobelet::Gobelet(Position goalposition):MediumLevelAction(goalposition){}

Gobelet::~Gobelet(){}

Etape::EtapeType Gobelet::getType()
{
    return Etape::GOBELET;
}

int Gobelet::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "gobelet";
#endif
        status++;
    }

    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
        status++;
    }

    else if (status == 2)
    {
        if (Command::isNear(goalPosition, 175.0f))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(goalPosition))
        {
#ifndef ROBOTHW
            qDebug() << "On baisse l'ascenseur";
#endif
            Ascenseur::getSingleton()->baisserAscenseur();
        status++;
        }
    }

    else if ((status <23) && (status > 0))  //On attend que l'ascenseur se baisse
    {
        status++;
    }

    else if (status == 23)
    {
#ifndef ROBOTHW
            qDebug() << "On ouvre les pinces";
#endif
            Pinces::getSingleton()->ouvrirPinces();
            status++;
    }

    else if ((status <43) && (status > 0))  //On attend que l'ascenseur ouvre les pinces
    {
        status++;
    }

    else if (status == 43)
    {
#ifndef ROBOTHW
            qDebug() << "On ferme les pinces";
#endif
            Pinces::getSingleton()->fermerPinces();
        status++;
    }

    else if ((status <63) && (status > 0))  //On attend que l'ascenseur ferme ses pinces
    {
        status++;
    }

    else if (status == 63)
    {
#ifndef ROBOTHW
        qDebug() << "Etape gobelet finie";
#endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
        status++;
    }

    else if (status == 64)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 65)
    {
        status = -1;
    }

    return status;
}
