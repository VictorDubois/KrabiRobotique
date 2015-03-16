#include "tapis.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"
//#include "brasdevant.h"


Tapis::Tapis(){}

Tapis::Tapis(Position position):MediumLevelAction(position)
{
    this->goBack = false;
    this->positionMarches = Position(1230,150);
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
            StrategieV2::lookAt(positionMarches);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(positionMarches))
        {
            //ouvrir le bras
            #ifndef ROBOTHW
            qDebug() << "On ouvre le brasdevant";
            #endif
           // BrasDevant::getBras()->expand();
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
      //  Pince::getPince()->open();
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
      //  BrasDevant::getBras()->collapse();
        status++;
    }

    else if ((status <= 155) && (status > -1))    //On attend que les bras se ferment.
    {
        status++;
    }

    else if (status == 156)
    {
        status = -1;
#ifndef ROBOTHW
        qDebug() << "Etape tapis finie";
#endif
    }

    return status;
}

