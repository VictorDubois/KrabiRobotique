#include "deposeFruits.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "container.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

DeposeFruits::DeposeFruits(){}

DeposeFruits::DeposeFruits(bool isBlue, Position positionDepart, float precision) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;

    this->precision = precision;


    status = 0;
}

DeposeFruits::~DeposeFruits()
{
    //dtor
}

int DeposeFruits::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "deposeFruits (mediumLevel) début";
#endif
        status = 1;
    }

    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(positionDepart, false);
        status++;
    }
    else if (status == 2) // mise en place du robot
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
#ifndef ROBOTHW
        qDebug() << "deposeFruits (mediumLevel) en position Départ";
#endif
            StrategieV2::setCurrentGoal(Position(positionDepart.getX(), 2000), true, 0.5);

            status++;
        }
    }
    else if(status < 500)//On attend pendant (53-3) * 5ms, le temps qu'e le bras sorte'on colle la bordure
    {
        status++;
    }
    else if (status == 500)
    {
#ifndef ROBOTHW
        qDebug() << "deposeFruits (mediumLevel) ouverture conteneur";
#endif
        Container::getSingleton()->open();
        status++;
    }
    else if(status < 1000)//On attend pendant (53-3) * 5ms, le temps qu'e le bras sorte'on colle la bordure
    {
        status++;
    }
    else if (status == 1000)
    {
        Container::getSingleton()->close();
#ifndef ROBOTHW
        qDebug() << "deposeFruits (mediumLevel) fermeture conteneur";
#endif
        StrategieV2::setCurrentGoal(positionDepart, false);
        status++;
    }

    else if(status == 1001)//On passe à l'étape suivante
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
#ifndef ROBOTHW
        qDebug() << "deposeFruits (mediumLevel) reparti";
#endif
            status = -1;
        }
    }

    return status;
}
