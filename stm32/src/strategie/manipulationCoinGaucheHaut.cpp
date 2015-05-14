#include "manipulationCoinGaucheHaut.h"
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

    else if (status == 4 + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status == 5 + ATTENTE + ATTENTE)
    {
        if (Ascenseur::getSingleton()->estEnBas())
        {
            status++;
        }
    }

    else if (status == 6 + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status < 6 + ATTENTE + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 6 + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else if (status < 7 +  ATTENTE + ATTENTE + ATTENTE)
    {
        if (Ascenseur::getSingleton()->estEnHaut())
        {
            status++;
        }
    }


    else if (status == 8 + ATTENTE + ATTENTE + ATTENTE)
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

    else if (status == 9 + ATTENTE + ATTENTE + ATTENTE)
    {
        if (Command::isNear(goalPosition, 200.0f))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 10 + ATTENTE + ATTENTE + ATTENTE)
    {
        if (Command::isLookingAt(this->goalPosition))
        {
            Pinces::getSingleton()->fermerPinces();
            status++;
        }
    }

    else if (status < 10 + ATTENTE + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 10 + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->ouvrirAscenseur();
        status++;
    }

    else if (status < 10 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        status++;
    }

    else if (status == 10 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status < 11 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        if (Ascenseur::getSingleton()->estEnBas())
        {
            status++;
        }
    }

    else if (status == 12 + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status < 12 + ATTENTE + ATTENTE + ATTENTE + ATTENTE + ATTENTE )
    {
        status++;
    }

    else if (status == 12 + ATTENTE + ATTENTE + ATTENTE + ATTENTE + ATTENTE)
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

