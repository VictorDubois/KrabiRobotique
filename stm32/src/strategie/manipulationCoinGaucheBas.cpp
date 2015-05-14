#include "manipulationCoinGaucheBas.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action


#ifndef ROBOTHW
#include <QDebug>
#endif

ManipulationCoinGaucheBas::ManipulationCoinGaucheBas(Position positionDepart, bool isYellow) : MediumLevelAction(positionDepart){
    Pinces::getSingleton()->ouvrirPinces();
    Ascenseur::getSingleton()->leverAscenseur();
    this->isYellow = isYellow;
}

ManipulationCoinGaucheBas::~ManipulationCoinGaucheBas(){}

Etape::EtapeType ManipulationCoinGaucheBas::getType()
{
    return Etape::COIN_GAUCHE_BAS;
}

int ManipulationCoinGaucheBas::update()
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
            qDebug() << "action ManipulationCoinGaucheBas";
    #endif
        this->goalPosition = Position(86,1755, isYellow);
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
        qDebug() << "Etape ManipulationCoinGaucheBas part2";
#endif
            this->goalPosition = Position(86, 1855, isYellow);
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
        this->goBack = true;
        status++;
    }

    else if (status < 206)
    {
        status++;
    }

    else if (status == 206)
    {
#ifndef ROBOTHW
        qDebug() << "Le robot se recentre";
#endif
        this->goalPosition =Position(260, 1575, isYellow);
        StrategieV2::setCurrentGoal(goalPosition, this->goBack);
        status++;
    }

    else if (status == 207)
    {
        if (Command::isNear(goalPosition))
        {
            this->goBack = false;
            status++;
        }
    }

    else
    {
        status = -1;
    }

    return status;
}

