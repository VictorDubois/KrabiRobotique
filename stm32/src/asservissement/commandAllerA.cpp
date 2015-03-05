#include "commandAllerA.h"
#include "odometrie.h"
#include <math.h>
#include "strategieV2.h"
#include "leds.h"

#ifndef abs
#define abs(x) fabs(x)
#endif

float diffAngle(float a, float b)
{
    float t = a-b;
    while (t > M_PI)
    {
        t -= 2*M_PI;
    }
    while (t < -M_PI)
    {
        t += 2*M_PI;
    }
    return t;
}

enum Signe
{
    SGN_NEG = -1,
    SGN_UNDEF = 0,
    SGN_POS = 1
};


    ////////////////////////////////
    //    CommandAllerEnArcA      //
    ////////////////////////////////

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

    m_fini = false;

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

Vitesse CommandAllerEnArcA::getLinearSpeed()
{
    return linSpeed;
}

Angle CommandAllerEnArcA::getAngularSpeed()
{
    return angSpeed;
}

// est ce que la commande a fini ?
bool CommandAllerEnArcA::fini() const
{
    return m_fini;
}

    ////////////////////////////////
    //       CommandAllerA        //
    ////////////////////////////////

CommandAllerA::CommandAllerA(Position p, bool reculer, float vitesseLineaireMax, float vitesseFin, float precisionAngle)
    : Command()
{
    but = p;
    vitesseLinMax = vitesseLineaireMax;
    vFin2 = vitesseFin*vitesseFin;
    m_reculer = reculer;
    linSpeed = Odometrie::odometrie->getVitesseLineaire();
    angSpeed = Odometrie::odometrie->getVitesseAngulaire();
    bonAngle = false;
    this->precisionAngle = -1.f;//precisionAngle;

    m_fini = false;
}

void CommandAllerA::update()
{
    float accAngMax = ACCELERATION_ANGULAIRE_MAX;
    float vitAngMax = VITESSE_ANGULAIRE_MAX;
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = vitesseLinMax;//VITESSE_LINEAIRE_MAX;

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

    //float angleVitesseMax = M_PI/10.0f;
    float angleVitesseMax = 0.5f*vitAngMax*vitAngMax/accAngMax;
    //float distanceVitesseMax = 350.0f;
    float distanceVitesseMax = 0.5f*(vitLinMax*vitLinMax-vFin2)/decLinMax;
    float angle = Odometrie::odometrie->getPos().getAngle();
    Position pos = Odometrie::odometrie->getPos().getPosition();
    Position delta = but-pos;
    float angleVise = atan2(delta.getY(),delta.getX());

    if (m_reculer)
        angleVise += M_PI;

    float diffAng = diffAngle(angleVise,angle);

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
            derniereDistance = 1000000.0f;
        }
        else
        {
            linSpeed *= 0.95f;
        }
    }

    // Check sharps
    StrategieV2::setTourneSurSoiMeme((!bonAngle)&&(abs(linSpeed)<0.2f));

    if (linSpeed > 0.2f)
        StrategieV2::enableSharpsGroup(true);
    else if (linSpeed < -0.2f)
        StrategieV2::enableSharpsGroup(false);
    else
        StrategieV2::emptySharpsToCheck();

    float distanceBut = delta.getNorme();

    bool distanceOk = /*(distanceBut > derniereDistance) || */(distanceBut < 30.0f);

    // vitesse angulaire
    if (distanceOk)
    {
        //vitAngMax = VITESSE_ANGULAIRE_SLOW_MAX;
        //linSpeed = 0.;
    }
    if (bonAngle && precisionAngle>0.)
    {
        angSpeed = 0.;
    }
    else if (abs(diffAng) > angleVitesseMax)
    {
        bool hasToDecelerate = /*(!distanceOk) && */(fabs(diffAng) < (angSpeed * angSpeed / accAngMax - accAngMax*2.));
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
    if (distanceBut > derniereDistance || distanceBut < 10.0f)
    {
        m_fini = true;
    }

    if (bonAngle)
    {

        if (fabs(diffAng) > angleMaxPourAvancer)
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
            float linSpeedVisee;
            if (m_reculer)
                linSpeedVisee = -sqrt(vFin2+2.0f*distanceBut*decLinMax);
            else
                linSpeedVisee = sqrt(vFin2+2.0f*distanceBut*decLinMax);

             if (m_reculer)
                linSpeed -= accLinMax;
             else
                linSpeed += accLinMax;

            if (abs(linSpeed) > abs(linSpeedVisee))
                linSpeed = linSpeedVisee;
        }
    }
}

void CommandAllerA::resetSpeeds()
{
    linSpeed = Odometrie::odometrie->getVitesseLineaire();
    angSpeed = Odometrie::odometrie->getVitesseAngulaire();
}

Vitesse CommandAllerA::getLinearSpeed()
{
    return linSpeed;
}

Angle CommandAllerA::getAngularSpeed()
{
    return angSpeed;
}

bool CommandAllerA::fini() const
{
    return m_fini;
}



    ////////////////////////////////
    //    CommandTournerVers      //
    ////////////////////////////////

CommandTournerVers::CommandTournerVers(Position p, float maxSpeed)
    : Command()
{
    but = p;
    butAngle = 0;
    angSpeed = 0;
    useAngle = false;

    m_fini = false;
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

    m_fini = false;
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
    float diffAng = diffAngle(angleVise,angle);

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

Angle CommandTournerVers::getAngularSpeed()
{
    return angSpeed;
}

bool CommandTournerVers::fini() const
{
    return m_fini;
}

    ////////////////////////////////
    //       CommandVirage        //
    ////////////////////////////////


// rayon > 0
// angle > 0 : vers la gauche, angle < 0 : vers la droite
CommandVirage::CommandVirage(float rayon, float angle, float vitesseLineaireMax, float vitesseFin)
{
    if (angle > 0.0f)
        rayonCourbure = rayon;
    else
        rayonCourbure = -rayon;
    linSpeed = Odometrie::odometrie->getVitesseLineaire();
    angSpeed = Odometrie::odometrie->getVitesseAngulaire();
    angleVise = angle + Odometrie::odometrie->getPos().getAngle();
    vFin2 = vitesseFin*vitesseFin;
    vitesseLinMax = vitesseLineaireMax;

    m_fini = false;
}

void CommandVirage::update()
{
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = vitesseLinMax;//VITESSE_LINEAIRE_MAX;

    float distanceVitesseMax = 0.5f*(vitLinMax*vitLinMax-vFin2)/decLinMax;

    float angleRestant = diffAngle(angleVise, Odometrie::odometrie->getPos().getAngle());
    float distanceRestante = abs(rayonCourbure*angleRestant);

    // gestion de si la commande a fini
    // si l'angle restant est bon ou si on a dépassé l'angle visé
    if (abs(angleRestant) < M_PI/90.0f || ((angleRestant > 0.0f) != (rayonCourbure > 0.0f)))
    {
        m_fini = true;
    }

    // phase de vitesse max
    if (distanceRestante > distanceVitesseMax)
    {
            linSpeed += accLinMax;
        if (linSpeed > vitLinMax)
            linSpeed = vitLinMax;
    }

    // phase de décéleration
    else
    {
        linSpeed = sqrt(vFin2+2.0f*distanceRestante*decLinMax);
    }

    // calcul de la vitesse angulaire
    angSpeed = linSpeed/rayonCourbure;
}

Vitesse CommandVirage::getLinearSpeed()
{
    return linSpeed;
}

Angle CommandVirage::getAngularSpeed()
{
    return angSpeed;
}

// est ce que la commande a fini ?
bool CommandVirage::fini() const
{
    return m_fini;
}


    ////////////////////////////////
    //      CommandAttendre       //
    ////////////////////////////////

CommandAttendre::CommandAttendre(int nbUpdates)
    : Command(), compte(nbUpdates)
{
}

void CommandAttendre::update()
{
    compte--;
}

Vitesse CommandAttendre::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandAttendre::getAngularSpeed()
{
    return 0.0f;
}

bool CommandAttendre::fini() const
{
    return (compte <= 0);
}


    ////////////////////////////////
    //      CommandTestAvancer    //
    ////////////////////////////////

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

    ////////////////////////////////
    //  CommandTestTournerGauche  //
    ////////////////////////////////


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
