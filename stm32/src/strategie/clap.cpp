#include "clap.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"
#include "brasLateraux.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

#define ATTENTE_ROTATION 500
#define ATTENTE_SORTIE_BRAS 10


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

    if (status == 0)//Début
    {
#ifndef ROBOTHW
        qDebug() << "clap";
#endif
        status++;
    }

    else if (status == 1)//Aller au point de départ
    {
        StrategieV2::setCurrentGoal(goalPosition, goBack);
        status++;
    }

    else if (status == 2)//Se tourner une fois au point de départ
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(positionArrivee);

            status++;
        }
    }

    else if ((status <= 3 + ATTENTE_ROTATION) && (status > -1 ))//On attend que le robot se tourne : 50ms par incrémentation du status
    {
        status++;
    }


    else if (status == 4 + ATTENTE_ROTATION)//Sortir le bras
    {
        //Ouvrir le bras
        if (positionArrivee.getX()<1500)
            BrasLateraux::getRight()->expand();
        else
            BrasLateraux::getLeft()->expand();

        status++;
    }

    else if ((status <= 5 + ATTENTE_ROTATION + ATTENTE_SORTIE_BRAS) && (status > -1 ))//On attend que le bras du robot s'ouvre : 50ms par incrémentation du status
    {
        status++;
    }

    else if (status == 6 + ATTENTE_ROTATION + ATTENTE_SORTIE_BRAS)//Avancer pour faire tomber le clap
    {
        StrategieV2::setCurrentGoal(positionArrivee, goBack);
        status++;
    }

    else if (status == 56 + ATTENTE_ROTATION + ATTENTE_SORTIE_BRAS)//Fermer le bras une fois passé
    {
        if (Command::isNear(positionArrivee))
        {
            if (positionArrivee.getX()<1500)
                BrasLateraux::getRight()->collapse();
            else
                BrasLateraux::getLeft()->collapse();
            status++;
        }
    }

    else if ((status <= 105 + ATTENTE_ROTATION + ATTENTE_SORTIE_BRAS) && (status > -1))
    {
        status++;
    }

    else if (status == 106 + ATTENTE_ROTATION + ATTENTE_SORTIE_BRAS){
        status = -1;
#ifndef ROBOTHW
        qDebug() << "Etape clap finie";
#endif
    }

    return status;
}
