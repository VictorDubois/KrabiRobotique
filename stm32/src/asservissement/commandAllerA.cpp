#include "commandAllerA.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "leds.h"
#include "angle.h"

#include <math.h>

#ifndef abs
    #define abs(x) fabs(x)
#endif

#ifndef ROBOTHW
    #include "debugwindow.h"
#endif

CommandAllerA::CommandAllerA(Position p, bool reculer, float vitesseLineaireMax, float vitesseFin, float precisionAngle)
    : Command(), smoothFactor(0.f), requireSmoothMovement(false), bonAngle(false), angleSmoothEnd(false)
{
    but = p;
    vitesseLinMax = vitesseLineaireMax;
    vFin2 = vitesseFin*vitesseFin;
    m_reculer = reculer;
    this->precisionAngle = -1.f;//precisionAngle;
}

void CommandAllerA::update()
{
    // maximum values
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = vitesseLinMax;//VITESSE_LINEAIRE_MAX;
    float vitLinIntermediate = vitesseLinMax/2.;

    if(this->getLimit())
    {
        vitLinMax = vitesseLinMax/3;
        allumerLED();
        allumerLED2();
    }
    else
    {
        //eteindreLED();
    }

    // settings
    //float angleVitesseMax = M_PI/10.0f;
    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    //float distanceVitesseMax = 350.0f;
    float distanceVitesseMax = 0.5f*(vitLinMax*vitLinMax-vFin2)/decLinMax;
    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();
    Position computedGoal = but;
    Position deltaFirst = but - pos;
    Position deltaNext;
    if (this->requireSmoothMovement)
        deltaNext = nextGoal - but;

    // distances
    float distanceNext = (this->requireSmoothMovement ? deltaNext.getNorme() : 0);
    // disable smooth if short moves
    /*if (this->requireSmoothMovement && distanceNext < 50.)
        this->requireSmoothMovement = false;*/
    float distanceIntermediate = (this->requireSmoothMovement ? deltaFirst.getNorme() : 0);

    bool isChangingToNext = false;

    // smooth movement
    Position delta;
    if (this->requireSmoothMovement)
    {
        if (distanceIntermediate > this->smoothFactor)
            delta = deltaFirst;
        else
        {
            isChangingToNext = true;
            delta = deltaFirst + (deltaNext - deltaFirst) * (0.5f - distanceIntermediate / (this->smoothFactor * 2.));
        }
    }
    else
        delta = computedGoal - pos;

#ifndef ROBOTHW
    DebugWindow::instance()->plot(4, "distance", distanceIntermediate / 100.);
#endif

    // distances
    float distanceFinal = (this->requireSmoothMovement ? delta.getNorme() + distanceNext : delta.getNorme());

    // angles
    float angleVise = atan2(delta.getY(),delta.getX());

    if (m_reculer)
        angleVise += M_PI;

    float diffAng = AngleTools::diffAngle(angleVise,angle);

    // reste sur place tant que le robot n'a pas le bon angle
    float angleMaxPourAvancer;
    if (precisionAngle<0.)
        angleMaxPourAvancer = M_PI/25.0f;//25.0f;
    else
        angleMaxPourAvancer = DEGTORAD(3.);//25.0f;
    if (!bonAngle)
    {
        if (fabs(diffAng) < angleMaxPourAvancer)
        {
            bonAngle = true;
            lastDistance = 1000000.0f;
        }
        else if (!fromSmoothMovement)
        {
            linSpeed *= 0.95f;
        }
    }

#ifndef ROBOTHW
    DebugWindow::instance()->plot(4, "distance", distanceIntermediate / 100.);
#endif

    // sharps
    StrategieV2::setTourneSurSoiMeme((!bonAngle)&&(abs(linSpeed)<0.2f));

    if (linSpeed > 0.2f)
        StrategieV2::enableSharpsGroup(true);
    else if (linSpeed < -0.2f)
        StrategieV2::enableSharpsGroup(false);
    else
        StrategieV2::emptySharpsToCheck();

    bool distanceOk = /*(distanceBut > derniereDistance) || */(distanceFinal < 30.0f);

    // vitesse angulaire
    if (distanceOk)
    {
        //vitAngMax = VITESSE_ANGULAIRE_SLOW_MAX;
        //linSpeed = 0.;
    }
    /*if (bonAngle && precisionAngle > 0.)
    {
        angSpeed = 0.;
    }
    else */

    if (fabs(diffAng) > angleVitesseMax / 10.f)
        angleSmoothEnd = false;
    /*else if (fabs(diffAng) < angleVitesseMax / 20.f)
        angleSmoothEnd = true;*/

#ifndef ROBOTHW
        qDebug() << angleSmoothEnd << fabs(diffAng);
#endif

    if (angleSmoothEnd)
    {
        angSpeed = diffAng*vitAngMax/angleVitesseMax;
    }
    else
    {
        bool hasToDecelerate = (fabs(diffAng) < (angSpeed * angSpeed / accAngMax - accAngMax*2.));

        if (diffAng > 0)
        {
            if (!hasToDecelerate)
                angSpeed += accAngMax;
            else if (angSpeed > accAngMax*2)
                angSpeed -= accAngMax*2;
            else
                angleSmoothEnd = true;

            if (angSpeed > vitAngMax)
                angSpeed = vitAngMax;
        }
        else
        {
            if (!hasToDecelerate)
                angSpeed -= accAngMax;
            else if (angSpeed < -accAngMax*2)
                angSpeed += accAngMax*2;
            else
                angleSmoothEnd = true;

            if (angSpeed < -vitAngMax)
                angSpeed = -vitAngMax;
        }

    }

    // vitesse angulaire
    /*if (abs(diffAng) > angleVitesseMax)
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
    }*/

    // vitesse linéaire
    if (bonAngle || fromSmoothMovement)
    {

        if (fabs(diffAng) > angleMaxPourAvancer && !isChangingToNext)
        {
            if (!fromSmoothMovement)
                linSpeed *= 0.97f;
        }
        else if (isChangingToNext)
        {
            float linSpeedVisee = (m_reculer ? -vitLinIntermediate : vitLinIntermediate);

            if (abs(linSpeed) < abs(linSpeedVisee))
            {
                linSpeed += (m_reculer ? -accLinMax : accLinMax);
                if (abs(linSpeed) > abs(linSpeedVisee))
                    linSpeed = linSpeedVisee;
            }
            else if (abs(linSpeed) > abs(linSpeedVisee))
            {
                linSpeed += (m_reculer ? accLinMax : -accLinMax);
                if (abs(linSpeed) < abs(linSpeedVisee))
                    linSpeed = linSpeedVisee;
            }
        }
        else if (distanceFinal > distanceVitesseMax)
        {
            linSpeed += (m_reculer ? -accLinMax : accLinMax);

            if (linSpeed > vitLinMax)
                linSpeed = vitLinMax;
            else if (linSpeed < -vitLinMax)
                linSpeed = -vitLinMax;
        }
        else
        {
            float linSpeedVisee = sqrt(vFin2+2.0f*distanceFinal*decLinMax);
            if (m_reculer)
                linSpeedVisee = -linSpeedVisee;

            linSpeed += (m_reculer ? -accLinMax : accLinMax);

            if (abs(linSpeed) > abs(linSpeedVisee))
                linSpeed = linSpeedVisee;

            //linSpeed = distanceBut * vitesseLinMax / distanceVitesseMax;
        }
    }

    if ((isChangingToNext && distanceIntermediate > lastDistance) || distanceFinal < 10.0f)
    {
        mFinished = true;
    }

    lastDistance = distanceIntermediate;
}

void CommandAllerA::smoothMovement(Position nextGoal, float smoothFactor)
{
    this->smoothFactor = smoothFactor;
    this->nextGoal = nextGoal;
    this->requireSmoothMovement = true;

    markAsSmooth();
}
