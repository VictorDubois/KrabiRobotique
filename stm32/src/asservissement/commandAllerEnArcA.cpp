#include "commandAllerEnArcA.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "leds.h"
#include "angle.h"

#ifndef abs
#define abs(x) fabs(x)
#endif

CommandAllerEnArcA::CommandAllerEnArcA(Position p, Position c, float v, bool reculer)
    : Command()
{
    but = p;
    centre = c;
    vMax = v;
    m_reculer = reculer;
    bonAngle = false;

    Position pos = Odometrie::odometrie->getPos().getPosition();
    float pmcx = pos.x-centre.x;
    float pmcy = pos.y-centre.y;
    float bmcx = but.x-centre.x;
    float bmcy = but.y-centre.y;
    if (pmcx*bmcy-pmcy*bmcx > 0.0f)
        cote = SGN_POS;
    else
        cote = SGN_NEG;
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
    /*
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

    // test si la commande a fini
    if ((cote == SGN_POS && sintheta < 0.0f) || (cote == SGN_NEG && sintheta > 0.0f) || (abs(sintheta) < M_PI/180.0f))
        m_fini = true;

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
*/
    // pour garder la trajectoire de cercle
//    std::cout << linSpeed << std::endl;
    /*
    if (abs(angSpeed) > abs(linSpeed/rVise))
        angSpeed = linSpeed/rVise;
    else if (abs(linSpeed) > abs(rVise*angSpeed))
        linSpeed = rVise*angSpeed;*/
}
