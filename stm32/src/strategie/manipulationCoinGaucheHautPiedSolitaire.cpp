#include "manipulationCoinGaucheHautPiedSolitaire.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action

#define ATTENTE 20

#ifndef ROBOTHW
#include <QDebug>
#endif

ManipulationCoinGaucheHautPiedSolitaire::ManipulationCoinGaucheHautPiedSolitaire(Position positionDepart, bool isYellow) : MediumLevelAction(positionDepart){
    Pinces::getSingleton()->ouvrirPinces();
    Ascenseur::getSingleton()->leverAscenseur();
    this->isYellow = isYellow;
}

ManipulationCoinGaucheHautPiedSolitaire::~ManipulationCoinGaucheHautPiedSolitaire(){}

Etape::EtapeType ManipulationCoinGaucheHautPiedSolitaire::getType()
{
    return Etape::SPOT_SOLITAIRE_COIN;
}

int ManipulationCoinGaucheHautPiedSolitaire::update()
{
    if (status == 0)
    {
        StrategieV2::setCurrentGoal(this->goalPosition);
        status++;
    }

    else if (status == 1)
    {
        if (Command::isNear(this->goalPosition))
        {
            status++;
        }
    }

    else if (status == 2)
    {
    #ifndef ROBOTHW
            qDebug() << "action ManipulationCoinGaucheHautPiedSolitaire";
    #endif
        this->goalPosition = Position(85,200, isYellow);
        StrategieV2::setCurrentGoal(this->goalPosition);
        status++;
    }

    else if (status == 3)
    {
        if (Command::isNear(goalPosition, 200.0f))
        {
            StrategieV2::lookAt(this->goalPosition);
            status++;
        }
    }

    else if (status == 4)
    {
        if (Command::isLookingAt(this->goalPosition))
        {
            Pinces::getSingleton()->fermerPinces();
            status++;
        }
    }

    else if (status < 4 + ATTENTE)
    {
        status++;
    }

    else if (status == 4 + ATTENTE)
    {
        Ascenseur::getSingleton()->ouvrirAscenseur();
        status++;
    }

    else if (status < 4 + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 5 + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status < 5 + ATTENTE + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 5 + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status < 5 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 5 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else if (status == 6 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        if (Ascenseur::getSingleton()->estEnHaut())
        {
            status++;
        }
    }


    else if (status == 7 + ATTENTE + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        status = -1;
    }

    return status;
}
