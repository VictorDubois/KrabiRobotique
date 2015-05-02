#include "pied.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Pied::Pied(){}

Pied::Pied(Position goalposition):MediumLevelAction(goalposition){}

Pied::~Pied(){}

int Pied::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "action pied";
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
            qDebug() << "On ouvre les pinces";
#endif
            Ascenseur::getSingleton()->ouvrirPincesAscenseur();
            status++;
        }
    }

    else if ((status <23) && (status > 0))  //On attend que l'ascenseur ouvre ses pinces
    {
        status++;
    }

    else if (status == 23)
    {
#ifndef ROBOTHW
            qDebug() << "On baisse l'ascenseur";
#endif
            Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if ((status <43) && (status > 0))  //On attend que l'ascenseur se baisse
    {
        status++;
    }

    else if (status == 43)
    {
#ifndef ROBOTHW
            qDebug() << "On ferme les pinces";
#endif
            Ascenseur::getSingleton()->fermerPincesAscenseur();
        status++;
    }

    else if ((status <63) && (status > 0))  //On attend que l'ascenseur ferme ses pinces
    {
        status++;
    }

    else if (status == 63)
    {
#ifndef ROBOTHW
            qDebug() << "On leve l'ascenseur";
#endif
            Ascenseur::getSingleton()->leverAscenseur();
        status++;
    }

    else if ((status <83) && (status > 0))  //On attend que l'ascenseur se leve
    {
        status++;
    }

    else if (status == 83)
    {
#ifndef ROBOTHW
        qDebug() << "Etape pied finie";
#endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
        status++;
        int nouveauNbrPiedsStockes = Ascenseur::getSingleton()->getNbrPiedsStockes() + 1;
        Ascenseur::getSingleton()->setNbrPiedsStockes(nouveauNbrPiedsStockes);
    }

    else if (status == 84)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 85)
    {
        status = -1;
    }

    return status;
}
