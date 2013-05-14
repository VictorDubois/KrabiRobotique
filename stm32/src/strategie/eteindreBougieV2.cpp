#include "eteindreBougieV2.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "marteaux.h"
#include "leds.h"
#include "asservissement.h"

EteindreBougieV2::EteindreBougieV2(Position pos, float angle, bool bas, bool check, bool mine, bool bvr) : MediumLevelAction(pos)
{
    angleToHave = (StrategieV2::getIsBlue() ? angle : wrapAngle(M_PI+angle));
    bougieBasse = bas;
    checked = check;
    mustPress = mine;
    bleuVersRouge = bvr;
    status = 0;
}

EteindreBougieV2::~EteindreBougieV2()
{
    //dtor
}

int EteindreBougieV2::update()
{
    allumerLED();
    if (status == 0)
    {
        status = 1;
        StrategieV2::setCurrentGoal(goalPosition, false, 0.50*VITESSE_LINEAIRE_MAX);
        // choose ourselves sharps to check
        StrategieV2::emptySharpsToCheck();
        StrategieV2::enableSharp(SharpSensor::FRONT_LEFT);
        StrategieV2::enableSharp(SharpSensor::FRONT_RIGHT);
        if (StrategieV2::getIsBlue())
            StrategieV2::enableSharp(SharpSensor::FRONT_SIDE_RIGHT);
        else
            StrategieV2::enableSharp(SharpSensor::FRONT_SIDE_LEFT);
    }
    else if (status == 1)
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        float distance = vect.getNorme();
        allumerLED();
        if (distance < 20.0)
        {
            status = 2;
            StrategieV2::lookAt(Odometrie::odometrie->getPos().getPosition()+Position(1000*cos(angleToHave), 1000*sin(angleToHave)));
        }
    }
    else if (status == 2)
    {
        float currentAngle = wrapAngle(Odometrie::odometrie->getPos().getAngle());
        allumerLED();
        if (fabs(currentAngle - angleToHave ) < 0.2)
        {
            status = 3;
            Marteaux::enfoncerMarteau(bougieBasse, bleuVersRouge); // baisser le marteau
            StrategieV2::setCommand(NULL);
        }
    }
    else if (status == 200) // on attend environ 2 secondes
    {
        Marteaux::releverMarteau(bougieBasse, bleuVersRouge); // baisser le marteau
        status++;
    }
    else if (status == 250) // on attend 2 secondes de plus
    {
        allumerLED();
        Marteaux::enfoncerMarteau(bougieBasse, bleuVersRouge); // baisser le marteau
        status++;
    }
    else if (status == 400) // on attend environ 2 secondes
    {
        Marteaux::rangerMarteau(bougieBasse, bleuVersRouge); // baisser le marteau
        status = -1;
    }
    else if (status > 2)
    {
        allumerLED();
        status++;
    }

    return status;

}

void EteindreBougieV2::setBleuVersRouge(bool bleuVrouge)
{
    bleuVersRouge = bleuVrouge;
}
