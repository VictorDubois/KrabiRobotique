#include "commandTournerVers.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "leds.h"
#include "angle.h"

#ifndef abs
#define abs(x) fabs(x)
#endif

CommandTournerVers::CommandTournerVers(Position p, float maxSpeed)
    : Command()
{
    but = p;
    butAngle = 0;
    angSpeed = 0;
    useAngle = false;

    signeAngle = SGN_UNDEF;

    maxAngSpeed = maxSpeed;
}

//#include <QDebug>

CommandTournerVers::CommandTournerVers(Angle a, float maxSpeed)
    : Command()
{
    but = Position();
    butAngle = a;
    angSpeed = 0;
    useAngle = true;

    signeAngle = SGN_UNDEF;

    maxAngSpeed = maxSpeed;
}

void CommandTournerVers::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = maxAngSpeed;
    // float angleVitesseMax = M_PI/6.0f;
    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();
    float angleVise;
    if (!useAngle)
    {
        Position delta = but-pos;
        angleVise = atan2(delta.getY(),delta.getX());
    }
    else
    {
        angleVise = butAngle;
    }
    float diffAng = AngleTools::diffAngle(angleVise,angle);

    // Check sharps
    StrategieV2::setTourneSurSoiMeme(true);


    //qDebug() << abs(angleVise)*180./3.14 << angleVitesseMax;

    if (abs(diffAng) > angleVitesseMax)
    {
        bool hasToDecelerate = (fabs(diffAng) < (angSpeed * angSpeed / accAngMax - accAngMax*2.));
        if (diffAng > 0)
        {
            if (!hasToDecelerate)
                angSpeed += accAngMax;
            else if (angSpeed > accAngMax*2)
                angSpeed -= accAngMax*2;

            if (angSpeed > vitAngMax)
                angSpeed = vitAngMax;
        }
        else
        {
            if (!hasToDecelerate)
                angSpeed -= accAngMax;
            else if (angSpeed < -accAngMax*2)
                angSpeed += accAngMax*2;

            if (angSpeed < -vitAngMax)
                angSpeed = -vitAngMax;
        }
    }
    else
    {
        angSpeed = diffAng*vitAngMax/angleVitesseMax;
    }


    // gestion de si la commande a fini
    /*if (abs(diff) < M_PI/90.0f)// || (signeAngle == SGN_NEG && diff > 0.0f) || (signeAngle == SGN_POS && diff < 0.0f))
    {
        m_fini = true;
    }
    else if (signeAngle == SGN_UNDEF && abs(diff) < 1.0f)
    {
        if (diff > 0.0f)
            signeAngle = SGN_POS;
        else
            signeAngle = SGN_NEG;
    }

    // calcul de la vitesse angulaire
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
    }*/

}

Vitesse CommandTournerVers::getLinearSpeed()
{
    return 0.0f;
}
