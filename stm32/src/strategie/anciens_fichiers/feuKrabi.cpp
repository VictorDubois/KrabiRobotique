#include "feuKrabi.h"
#include "strategieV2.h"
#ifndef ROBOTHW
#include <QDebug>
#endif

FeuKrabi::FeuKrabi(){}

FeuKrabi::FeuKrabi(bool isBlue, Position positionDepart, Position positionFeu, float precision) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->positionFeu = positionFeu;
    this->precision = precision;
    status = 0;
    bracquemart = Brak::getSingleton();
    positionEtape = Position(positionDepart.getX() + 150, positionDepart.getY(), isBlue);
}

int FeuKrabi::update()
{
    if (status == 0)
        status++;

    /*else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(positionDepart, false);
        bracquemart->positionFeuBasTorche();
#ifndef ROBOTHW
            qDebug() << "abaissage du bras";
#endif
        status++;
    }
    else if (status == 2)
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
            StrategieV2::setCurrentGoal(this->positionEtape, false, 1.0, 3.0f);
#ifndef ROBOTHW
            qDebug() << "arrivé en étape 3, direction vers la 4";
#endif
            status++;
        }
    }
    else if (status == 3)
    {
        Position vect = positionEtape - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this-> precision)
        {
            //StrategieV2::lookAt(this->positionFeu, 0.01);
#ifndef ROBOTHW
            qDebug() << "regardage du feu";
#endif
            status++;
        }
    }
    else if (status < 103)
    {
        bracquemart->positionBasse();
        bracquemart->attraperFeu();
#ifndef ROBOTHW
            qDebug() << "attrapage du feu";
#endif
            status++;
    }
    else if (status < 203)
    {
        status++;
    }
    else if (status == 203)
    {
        bracquemart->positionIntermediaire();
#ifndef ROBOTHW
            qDebug() << "remontage du bras avec le feu";
#endif
        status++;
    }
    else if (status < 253)
    {
        status++;
    }
    else if (status == 253)
    {
        status = -1;
    }*/

    return status;
}

FeuKrabi::~FeuKrabi()
{
    //dtor
}
