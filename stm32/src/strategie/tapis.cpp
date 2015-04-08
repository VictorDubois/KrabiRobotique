#include "tapis.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Tapis::Tapis(){}

Tapis::Tapis(Position position):MediumLevelAction(position)  //si cote est true on veut poser le tapis droit, si non c'est le tapis gauche
{
    if (position == Position(1000, 750))
    {
        this->positionLookAt = Position(0, 300);
        this->cote = 0;
    };
    if (position == Position(1450, 750))
    {
        this->positionLookAt = Position(3000, 200);
        this->cote = 1;
    };
}


Tapis::~Tapis(){}

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
            StrategieV2::lookAt(positionLookAt);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(positionLookAt))
        {
            //ouvrir le bras
#ifndef ROBOTHW
            qDebug() << "On ouvre le bras";
#endif

            BrasTapis::getSingleton(cote)->ouvrirBras();
            status++;
        }
    }

    else if ((status <= 23) && (status > -1 ))    //On attend que les bras du robot s'ouvrent : 50ms par incrémentation du status
    {
        status++;
    }

    else if (status == 24)
    {
        //lacher les tapis
#ifndef ROBOTHW
        qDebug() << "On ouvre les pinces pour lacher les tapis";
#endif
        BrasTapis::getSingleton(cote)->ouvrirPince();
        status++;
    }

    else if ((status <= 44) && (status > -1 ))    //On attend que la pince s'ouvre
    {
        status++;
    }

    else if (status == 45)
    {
        //fermer bras
#ifndef ROBOTHW
        qDebug() << "On ferme les Pinces";
#endif
        BrasTapis::getSingleton(cote)->fermerPince();
        status++;
    }

    else if ((status <= 65) && (status > -1 ))    //On attend que la pince se ferme
    {
        status++;
    }

    else if (status == 66)
    {
        //fermer bras
#ifndef ROBOTHW
        qDebug() << "On ferme le bras";
#endif
        BrasTapis::getSingleton(cote)->fermerBras();
        status++;
    }

    else if ((status <= 87) && (status > -1))    //On attend que les bras se ferment.
    {
        status++;
    }

    else if (status == 88)
    {
#ifndef ROBOTHW
        qDebug() << "Etape tapis finie";
#endif
        status = -1;
    }

    return status;
}

