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
        //Ne compile plus avec le nouvel enum des SHARPS
        /*StrategieV2::emptySharpsToCheck();
        StrategieV2::enableSharp(SharpSensor::FRONT_LEFT);
        StrategieV2::enableSharp(SharpSensor::FRONT_RIGHT);
        if (StrategieV2::getIsBlue())
            StrategieV2::enableSharp(SharpSensor::FRONT_SIDE_RIGHT);
        else
            StrategieV2::enableSharp(SharpSensor::FRONT_SIDE_LEFT);
        if (this->checked && !this->mustPress)
            status = -1;*/
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
    else if (status == 100) //
    {
        Marteaux::releverMarteau(bougieBasse, bleuVersRouge); //
        status++;
    }
    else if (status == 150) //
    {
        allumerLED();
        Marteaux::enfoncerMarteau(bougieBasse, bleuVersRouge); //
        status++;
    }
    else if (status == 200) //
    {
        if (bougieBasse)
            Marteaux::rangerMarteau(bougieBasse, bleuVersRouge); //
        else
            Marteaux::releverMarteau(bougieBasse, bleuVersRouge); //
        status++;
    }
    else if (status == 250)
    {
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
