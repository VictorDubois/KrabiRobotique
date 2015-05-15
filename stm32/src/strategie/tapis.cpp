#include "tapis.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

#define GRANDE_ATTENTE 50

Tapis::Tapis(){}

Tapis::Tapis(Position position):MediumLevelAction(position)
{
    this->toLookAt = M_PI/2;
    if (position == Position(1070, 850, StrategieV2::getIsYellow()))
    {
            this->cote = BrasTapis::GAUCHE;
    }
    if (position == Position(1420, 850, StrategieV2::getIsYellow()))
    {
            this->cote = BrasTapis::DROIT;
    }
}

Tapis::~Tapis(){}

Etape::EtapeType Tapis::getType()
{
    return Etape::TAPIS;
}

int Tapis::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
                qDebug() << "tapis";
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
            StrategieV2::lookAt(toLookAt);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(toLookAt))
        {
            //ouvrir le bras
#ifndef ROBOTHW
            qDebug() << "On ouvre le bras";
#endif

            BrasTapis::getSingleton(cote)->ouvrirBras();
            status++;
        }
    }

    else if (status < 3 + GRANDE_ATTENTE)
    {
        status++;
    }

    else if (status == 3 + GRANDE_ATTENTE)
    {
        //fermer bras
#ifndef ROBOTHW
        qDebug() << "On ferme le bras";
#endif
        BrasTapis::getSingleton(cote)->fermerBras();
        status++;
    }

    else if (status < 3 + GRANDE_ATTENTE + GRANDE_ATTENTE)
    {
        status++;
    }

    else if (status == 3 + GRANDE_ATTENTE + GRANDE_ATTENTE)    //On attend que les bras se ferment.
    {
#ifndef ROBOTHW
        qDebug() << "Etape tapis finie";
#endif
        status = -1;
    }
    return status;
}

