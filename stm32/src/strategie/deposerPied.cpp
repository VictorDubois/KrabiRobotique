#include "deposerPied.h"
#include "ascenseur.h"
#include "pinces.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif

DeposerPied::DeposerPied(){}

DeposerPied::DeposerPied(Position goalposition):MediumLevelAction(goalposition){}

DeposerPied::~DeposerPied(){}

int DeposerPied::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "deposerPied";
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
        if (Command::isNear(goalPosition))
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
            qDebug() << "On ouvre les pinces";
#endif
            Pinces::getSingleton()->ouvrirPinces();
        status++;
        }
    }

    else if ((status <23) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =23) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        Ascenseur::baisserAscenseur();
        status++;
    }

    else if ((status <43) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =43) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        Ascenseur::ouvrirAscenseur();
        status++;
    }


    else if ((status <63) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =63) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        this->goBack = true;
        status++;
    }

    else if ((status <74) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =74) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        Ascenseur::fermerAscenseur();
        status++;
    }

    else if ((status <84) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =84) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        Pinces::fermerPinces();
        status++;
    }

    else if ((status <104) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if (status == 104)
    {
        status = -1;
    }

    return status;
}

