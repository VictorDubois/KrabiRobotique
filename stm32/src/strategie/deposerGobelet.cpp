#include "deposerGobelet.h"
#include "pinces.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

DeposerGobelet::DeposerGobelet(){}

DeposerGobelet::DeposerGobelet(Position goalposition):MediumLevelAction(goalposition){}

DeposerGobelet::~DeposerGobelet(){}

int DeposerGobelet::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "deposerGobelet";
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
            qDebug() << "On lache le gobelet";
#endif
            Pinces::getSingleton()->ouvrirPinces();
        status++;
        }
    }

    else if ((status <23) && (status > 0))  //On attend que les pinces aient laché le gobelet.
    {
        status++;
    }

    else if (status == 23)
    {
#ifndef ROBOTHW
            qDebug() << "On referme les pinces";
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
        status = -1;
    }

    return status;
}
