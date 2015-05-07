#include "commandVirage.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "leds.h"
#include "angle.h"

#ifndef abs
#define abs(x) fabs(x)
#endif

// rayon > 0
// angle > 0 : vers la gauche, angle < 0 : vers la droite
CommandVirage::CommandVirage(float rayon, float angle, float vitesseLineaireMax, float vitesseFin)
{
    if (angle > 0.0f)
        rayonCourbure = rayon;
    else
        rayonCourbure = -rayon;
    angleVise = angle + Odometrie::odometrie->getPos().getAngle();
    vFin2 = vitesseFin*vitesseFin;
    vitesseLinMax = vitesseLineaireMax;
}

void CommandVirage::update()
{
    float accLinMax = ACCELERATION_LINEAIRE_MAX;
    float decLinMax = DECELERATION_LINEAIRE_MAX;
    float vitLinMax = vitesseLinMax;//VITESSE_LINEAIRE_MAX;

    float distanceVitesseMax = 0.5f*(vitLinMax*vitLinMax-vFin2)/decLinMax;

    float angleRestant = AngleTools::diffAngle(angleVise, Odometrie::odometrie->getPos().getAngle());
    float distanceRestante = abs(rayonCourbure*angleRestant);

    // gestion de si la commande a fini
    // si l'angle restant est bon ou si on a dépassé l'angle visé
    if (abs(angleRestant) < M_PI/90.0f || ((angleRestant > 0.0f) != (rayonCourbure > 0.0f)))
    {
        mFinished = true;
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
