#include "tapis.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"
//#include "brasdevant.h"


Tapis::Tapis(){}

Tapis::Tapis(Position position):MediumLevelAction(position)  //si cote est true on veut poser le tapis droit, si non c'est le tapis gauche
{
    if (position == Position(1950, 700))
    {
        this->positionLookAt = Position(3000, 400);
        this->cote = "droit";
    };
    if (position == Position(1550, 700))
    {
        this->positionLookAt = Position(0, 300);
        this->cote = "gauche";
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
            qDebug() << "On ouvre le brasdevant";
            #endif

            BrasTapis::getSingleton(cote)->ouvrirBras();
            status++;
        }
    }

    else if ((status <= 53) && (status > -1 ))    //On attend que les bras du robot s'ouvrent : 50ms par incrémentation du status
    {
        status++;
    }

    else if (status == 54)
    {
        //lacher les tapis
        #ifndef ROBOTHW
        qDebug() << "On ouvre la pince pour lacher les tapis";
        #endif
        BrasTapis::getSingleton(cote)->ouvrirPince();
        status++;
    }

    else if ((status <= 104) && (status > -1 ))    //On attend que la pince s'ouvre
    {
        status++;
    }

    else if (status == 105)
    {
        //fermer bras
        #ifndef ROBOTHW
        qDebug() << "On ferme le bras";
        #endif
        BrasTapis::getSingleton(cote)->fermerPince();
        status++;
    }

    else if ((status <= 155) && (status > -1 ))    //On attend que la pince se ferme
    {
        status++;
    }

    else if (status == 156)
    {
        //fermer bras
        #ifndef ROBOTHW
        qDebug() << "On ferme le bras";
        #endif
        BrasTapis::getSingleton(cote)->fermerBras();
        status++;
    }

    else if ((status <= 206) && (status > -1))    //On attend que les bras se ferment.
    {
        status++;
    }

    else if (status == 257)
    {
        status = -1;
#ifndef ROBOTHW
        qDebug() << "Etape tapis finie";
#endif
    }

    return status;
}

