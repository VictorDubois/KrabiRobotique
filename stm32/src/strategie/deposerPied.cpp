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

DeposerPied::DeposerPied(Position goalposition, bool isYellow):MediumLevelAction(goalposition){
    if (goalposition == Position(250, 1000, isYellow))
    {
        this->positionRetournement = Position(700, 1000, isYellow);
    }
   /* if (goalposition == Position(, , isYellow))
         this->positionRetournement =
     if (goalposition == Position(, , isYellow))
          this->positionRetournement =*/
    else
    {
        this->positionRetournement = goalPosition;
    }
}

DeposerPied::~DeposerPied(){}

Etape::EtapeType DeposerPied::getType()
{
    return Etape::DEPOSER_PIED;
}

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
            Pinces::getSingleton()->ouvrirPinces();
        status++;
        }
    }

    else if ((status <23) && (status > 0))  //On attend que les pinces soient ouvertes
    {
        status++;
    }

    else if ((status =23) && (status > 0))  //On baisse l'ascenseur
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if ((status <43) && (status > 0))  //On attend que l'ascenseur se baisse
    {
        status++;
    }

    else if ((status =43) && (status > 0))  //On ouvre l'ascenseur
    {
        Ascenseur::getSingleton()->ouvrirAscenseur();
        status++;
    }


    else if ((status <63) && (status > 0))  //On attend que l'ascenseur soit ouvert
    {
        status++;
    }

    else if ((status =63) && (status > 0))  //On dit à Krabi de se déplacer à partir de maintenant à l'envers
    {
        this->goBack = true;
        status++;
    }


    else if ((status =64) && (status > 0))  //Le robot se déplace jusqu'à un autre point du graphe en arrière.
    {
        StrategieV2::setCurrentGoal(this->positionRetournement, this->goBack);
        status++;;
    }

    else if ((status =65) && (status > 0)) //Le robot se déplace jusqu'à un autre point du graphe en arrière.
    {
        if (Command::isNear(positionRetournement))
        status++;
    }

    else if ((status =66) && (status > 0))  //On ferme l'ascenceur
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if ((status <84) && (status > 0))  //On attend que l'ascenseur soit ferme
    {
        status++;
    }

    else if ((status =84) && (status > 0))  //Les pinces se ferment
    {
        Pinces::getSingleton()->fermerPinces();
        status++;
    }

    else if ((status <104) && (status > 0))  //On attend que les pinces soient fermees
    {
        status++;
    }

    else if (status == 104) //action finie
    {
        status = -1;
    }

    return status;
}

