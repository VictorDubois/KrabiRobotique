#include "tireLances.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "positionPlusAngle.h"
#include "canonLances.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

TireLances::TireLances()
{

}

CanonLances* canon = CanonLances::getSingleton();

TireLances::TireLances(bool isBlue, Position positionDepart, bool coteDuMammouth, int number, float precisionPosition, float precisionAngle) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->coteDuMammouth = coteDuMammouth;
//    this->bordureFeu = bordureFeu;
//    this->sensFeu = sensFeu;
//    this->coteDuFeu = coteDuFeu;
    //this->precision = precision;
    this->precisionPosition = precisionPosition;
    this->precisionAngle = precisionAngle;
    this->numberLances = number;
    this->numberDone = 0;
    this->timerEnd = 0;
    this->fireLow = false;

    if(coteDuMammouth == COTE_NOTRE_DEPART)
    {
        lookAtDirection = (this->isBlue ? DEGTORAD(8.) : -DEGTORAD(8.)) - M_PI/2;
    }
    else if(coteDuMammouth == COTE_DEPART_ADVERSAIRE)
    {
        lookAtDirection = (this->isBlue ? -DEGTORAD(8.) : DEGTORAD(8.)) - M_PI/2;
    }

    status = 0;
}

TireLances::~TireLances()
{
    //dtor
}

int TireLances::update()
{
    if (status == 0)
        status = 1;

    else if (status == 1) // mise en place du robot
    {
#ifndef ROBOTHW
        qDebug() << "Lances";
#endif
        StrategieV2::setCurrentGoal(positionDepart, false);
        status++;
    }
    else if (status == 2) // position tir 1
    {
        if(Command::isNear(positionDepart, (int) this->precisionPosition))//vect.getNorme() < (int) this->precisionPosition)
        {
            StrategieV2::emptySharpsToCheck();
            StrategieV2::lookAt(lookAtDirection);
            status++;
        }
    }
    else if(status == 3)
    {
        if(Command::isLookingAt(lookAtDirection, this->precisionAngle))
        {
            CanonLances::getSingleton()->shootAtWill();
            //StrategieV2::lookAt(this->directionsTire[0]);//On aligne le tir en direction du mammouth
            status++;
        }
    }
    else if(numberDone<numberLances && ((status-4)%300==120))
    {
        if (numberDone!=0)
            StrategieV2::lookAt(Odometrie::odometrie->getPos().angle - (this->isBlue ? DEGTORAD(2.8) : -DEGTORAD(2.8)), 0.002);
        CanonLances::getSingleton()->arm();
        if (fireLow)
            CanonLances::getSingleton()->shootAtWill();
        else
            CanonLances::getSingleton()->shootAtWillLow();
        fireLow = !fireLow;
        status++;
    }
    else if(numberDone<numberLances && ((status-4)%300==0))
    {
        CanonLances::getSingleton()->fire();
        numberDone++;
        status++;
    }
    else if(numberDone<numberLances)
    {
        status++;
    }
    else if (timerEnd==0)
    {
        status++;
        timerEnd = status;
    }
    else if (status < timerEnd + 500)
    {
        status++;
    }
    else
    {
        CanonLances::getSingleton()->stopShootAtWill();
        status = -1;
    }

    return status;
}

int TireLances::getNumber()
{
    return this->numberLances;
}

int TireLances::getNumberDone()
{
    return this->numberDone;
}
