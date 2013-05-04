#include "commandAllerA.h"
#include "odometrie.h"
#include <math.h>






CommandAllerEnArcA::CommandAllerEnArcA(Position p, Position c, float v, bool reculer)
    : Command()
{
    but = p;
    centre = c;
    vMax = v;
    m_reculer = reculer;
    linSpeed = Odometrie::odometrie->getVitesseLineaire();
    angSpeed = Odometrie::odometrie->getVitesseAngulaire();
    bonAngle = false;
}

void CommandAllerEnArcA::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = vMax;//VITESSE_LINEAIRE_MAX;

    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();

    float rayon = (centre-but).getNorme();

/*
    float vdx = pos.y-but.y;
    float vdy = but.x-pos.x;
    float pmcx = pos.x-centre.x;
    float pmcy = pos.y-centre.y;
    float vdnorme = rayon/sqrt(vdx*vdx+vdy*vdy);
    if (pmcy*vdx+pmcx*vdy < 0) // determinant pour connaitre le sens
        vdnorme = -vdnorme;
    Position pInter(centre.x + vdnorme*vdx, centre.y + vdnorme*vdy);
*/
    float pmcx = pos.x-centre.x;
    float pmcy = pos.y-centre.y;
    float bmcx = but.x-centre.x;
    float bmcy = but.y-centre.y;
    float sintheta = (pmcx*bmcy-pmcy*bmcx)/(rayon*sqrt(pmcx*pmcx+pmcy*pmcy));
    float theta = asin(sintheta);
    float aVise = atan2(pmcy,pmcx)+0.85f*theta;
    Position pVise(centre.x+rayon*cos(aVise), centre.y+rayon*sin(aVise));
    float vmpx = pVise.x-pos.x;
    float vmpy = pVise.y-pos.y;
    float d2 = sqrt(vmpx*vmpx+vmpy*vmpy);
    float an = atan2(vmpy,vmpx);
    float rVise = 0.5f*d2/sin(an-angle);

    float linSpeedVise = vitLinMax;
    float angSpeedVise = vitLinMax/rVise;
    if (angSpeedVise > vitAngMax)
    {
        linSpeedVise *= vitAngMax/angSpeedVise;
        angSpeedVise = vitAngMax;
    }

    float distance = theta*rVise; // (Odometrie::odometrie->getPos().getPosition() - but).getNorme();
    float distanceVitesseMax = 0.5f*vitLinMax*vitLinMax/decLinMax;
    if (distance < distanceVitesseMax)
    {
        linSpeedVise = sqrt(2*distance*decLinMax);
        angSpeedVise = linSpeedVise/rVise;
    }
    if (linSpeed > linSpeedVise)
    {
        if (linSpeed-linSpeedVise < decLinMax)
            linSpeed = linSpeedVise;
        else
            linSpeed -= decLinMax;
    }
    else
    {
        if (linSpeedVise-linSpeed < accLinMax)
            linSpeed = linSpeedVise;
        else
            linSpeed += accLinMax;
    }

    if (angSpeed > angSpeedVise)
    {
        if (angSpeed-angSpeedVise < accAngMax)
            angSpeed = angSpeedVise;
        else
            angSpeed -= accAngMax;
    }
    else
    {
        if (angSpeedVise-angSpeed < accAngMax)
            angSpeed = angSpeedVise;
        else
            angSpeed += accAngMax;
    }

    // pour garder la trajectoire de cercle
//    std::cout << linSpeed << std::endl;
    if (abs(angSpeed) > abs(linSpeed/rVise))
        angSpeed = linSpeed/rVise;
    else if (abs(linSpeed) > abs(rVise*angSpeed))
        linSpeed = rVise*angSpeed;


}

Vitesse CommandAllerEnArcA::getLinearSpeed()
{
    return linSpeed;
}

Angle CommandAllerEnArcA::getAngularSpeed()
{
    return angSpeed;
}












CommandAllerA::CommandAllerA(Position p, bool reculer)
    : Command()
{
    but = p;
    m_reculer = reculer;
    linSpeed = Odometrie::odometrie->getVitesseLineaire();
    angSpeed = Odometrie::odometrie->getVitesseAngulaire();
    bonAngle = false;
}

void CommandAllerA::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = VITESSE_LINEAIRE_MAX;

    //float angleVitesseMax = M_PI/10.0f;
    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    //float distanceVitesseMax = 350.0f;
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
        {
            bonAngle = true;
        }
        else
        {
            linSpeed *= 0.95f;
            return;
        }
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
        /*if (m_reculer)
            linSpeed = -distanceBut*vitLinMax/distanceVitesseMax;
        else
            linSpeed = distanceBut*vitLinMax/distanceVitesseMax;*/
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



CommandTournerVers::CommandTournerVers(Position p)
    : Command()
{
    but = p;
    linSpeed = 0;
    angSpeed = 0;
}

void CommandTournerVers::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    // float angleVitesseMax = M_PI/6.0f;
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
        //angSpeed = diff*vitMax/angleVitesseMax;
        if (diff >= 0)
            angSpeed = sqrt(2.0f*diff*accAngMax);
        else
            angSpeed = -sqrt(-2.0f*diff*accAngMax);
    }

}

Vitesse CommandTournerVers::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandTournerVers::getAngularSpeed()
{
    return angSpeed;
}




CommandTestAvancer::CommandTestAvancer()
    : Command()
{
}

void CommandTestAvancer::update()
{
}

Vitesse CommandTestAvancer::getLinearSpeed()
{
    return VITESSE_LINEAIRE_MAX;
}

Angle CommandTestAvancer::getAngularSpeed()
{
    return 0.0f;
}




CommandTestTournerGauche::CommandTestTournerGauche()
    : Command()
{
}

void CommandTestTournerGauche::update()
{
}

Vitesse CommandTestTournerGauche::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandTestTournerGauche::getAngularSpeed()
{
    return VITESSE_ANGULAIRE_MAX;
}

