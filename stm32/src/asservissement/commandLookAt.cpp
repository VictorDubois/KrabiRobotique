#include "commandLookAt.h"
#include "odometrie.h"

#include <math.h>

float abs(float x)
{
    return (x<0 ? -x : x);
}

float diffAngle(float a, float b)
{
    float t = a-b;
    float i = floor((t+M_PI)/2.f/M_PI);

    return t-i*2*M_PI;
}

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

// le robot se tourne vers le point donné et y avance
CommandAllerA::CommandAllerA(Position objectif, bool reculer)
    : Command()
{
    but = objectif;
    m_reculer = reculer;
    linSpeed = 0;
    angSpeed = 0;
    bonAngle = false;
}

void CommandAllerA::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = 0.017f;
    float vitLinMax = VITESSE_LINEAIRE_MAX;

    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    float distanceVitesseMax = 0.5f*vitLinMax*vitLinMax/decLinMax;

    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();

    Position delta = but-pos;
    float angleVise = atan2(delta.getY(),delta.getX());

    if (m_reculer)
        angleVise += M_PI;

    float diffAng = diffAngle(angleVise,angle);

    // vitesse angulaire
    if (abs(diffAng) > angleVitesseMax)
    {
         if (diffAng > 0)
            angSpeed += accAngMax;
         else
            angSpeed -= accAngMax;

        if (angSpeed > vitAngMax)
            angSpeed = vitAngMax;
        else if (angSpeed < -vitAngMax)
            angSpeed = -vitAngMax;
    }
    else
    {
        angSpeed = diffAng*vitAngMax/angleVitesseMax;
    }

    // reste sur place tant que le robot n'a pas le bon angle
    float angleMaxPourAvancer = M_PI/25.0f;
    if (!bonAngle)
    {
        if (abs(diffAng) < angleMaxPourAvancer)
            bonAngle = true;
        else
            return;
    }

    // vitesse linéaire
    float distanceBut = delta.getNorme();

    if (abs(diffAng) > angleMaxPourAvancer)
    {
        linSpeed *= 0.97f;
    }
    else if (distanceBut > distanceVitesseMax)
    {
         if (m_reculer)
            linSpeed -= accLinMax;
         else
            linSpeed += accLinMax;

        if (linSpeed > vitLinMax)
            linSpeed = vitLinMax;
        else if (linSpeed < -vitLinMax)
            linSpeed = -vitLinMax;
    }
    else
    {
        if (m_reculer)
            linSpeed = -sqrt(2*distanceBut*decLinMax);
        else
            linSpeed = sqrt(2*distanceBut*decLinMax);
    }
}

Vitesse CommandAllerA::getLinearSpeed()
{
    return linSpeed;
}

Angle CommandAllerA::getAngularSpeed()
{
    return angSpeed;
}
