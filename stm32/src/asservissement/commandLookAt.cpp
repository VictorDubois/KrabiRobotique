#include "commandLookAt.h"
#include "odometrie.h"

#include <math.h>


// le robot se tourne vers le point donné
CommandLookAt::CommandLookAt(Position objectif)
    : Command()
{
    but = objectif;
    angSpeed = 0;
}

void CommandLookAt::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();
    Position delta = but-pos;
    float angleVise = atan2(delta.getY(),delta.getX());
    float diff = diffAngle(angleVise,angle);

    if (abs(diff) > angleVitesseMax)
    {
         if (diff > 0)
            angSpeed += accAngMax;
         else if (diff < 0)
            angSpeed -= accAngMax;

        if (angSpeed > vitAngMax)
            angSpeed = vitAngMax;
        else if (angSpeed < -vitAngMax)
            angSpeed = -vitAngMax;
    }
    else
    {
        if (diff >= 0)
            angSpeed = sqrt(2.0f*diff*accAngMax);
        else
            angSpeed = -sqrt(-2.0f*diff*accAngMax);
    }
}

Vitesse CommandLookAt::getLinearSpeed()
{
    return 0.0;
}

Angle CommandLookAt::getAngularSpeed()
{
    return angSpeed;
}

