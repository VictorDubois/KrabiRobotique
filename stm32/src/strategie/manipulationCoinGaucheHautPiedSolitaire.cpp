#include "manipulationCoinGaucheHautPiedSolitaire.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action


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

    else if (status < 24)
    {
        status++;
    }

    else if (status == 24)
    {
        Ascenseur::getSingleton()->ouvrirAscenseur();
        status++;
    }

    else if (status < 44)
    {
        status++;
    }

    else if (status == 44)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status < 64)
    {
        status++;
    }

    else if (status == 64)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status < 84)
    {
        status++;
    }

    else if (status == 84)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else if (status < 104)
    {
        status++;
    }


    else if (status == 104)
    {
        status = -1;
    }

    return status;
}
