#include "manipulationCoinGaucheHaut.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action


#ifndef ROBOTHW
#include <QDebug>
#endif

ManipulationCoinGaucheHaut::ManipulationCoinGaucheHaut(Position positionDepart, bool isYellow) : MediumLevelAction(positionDepart){
    Pinces::getSingleton()->ouvrirPinces();
    Ascenseur::getSingleton()->leverAscenseur();
    this->isYellow = isYellow;
}

ManipulationCoinGaucheHaut::~ManipulationCoinGaucheHaut(){}

Etape::EtapeType ManipulationCoinGaucheHaut::getType()
{
    return Etape::COIN_GAUCHE_HAUT;
}

int ManipulationCoinGaucheHaut::update()
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
            qDebug() << "action ManipulationCoinGaucheHaut";
    #endif
        this->goalPosition = Position(850,210, isYellow);
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
        if (Ascenseur::getSingleton()->getNbrPiedsStockes()==3)
        {
            status = -1;
        }

        else
        {
#ifndef ROBOTHW
        qDebug() << "Etape ManipulationCoinGaucheHaut part2";
#endif
            this->goalPosition = Position(850, 110, isYellow);
            StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
            Pinces::getSingleton()->ouvrirPinces();
            status++;
        }
    }

    else if (status == 105)
    {
        if (Command::isNear(goalPosition, 200.0f))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 106)
    {
        if (Command::isLookingAt(this->goalPosition))
        {
            Pinces::getSingleton()->fermerPinces();
            status++;
        }
    }

    else if (status < 126)
    {
        status++;
    }

    else if (status == 126)
    {
        Ascenseur::getSingleton()->ouvrirAscenseur();
        status++;
    }

    else if (status < 146)
    {
        status++;
    }

    else if (status == 146)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status < 166)
    {
        status++;
    }

    else if (status == 166)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status < 186)
    {
        status++;
    }

    else if (status == 186)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else
    {
        status = -1;
    }

    return status;
}

