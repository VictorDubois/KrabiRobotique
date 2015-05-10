#include "pidFilterAngle.h"

PIDFilterAngle::PIDFilterAngle() :
    sommeErreurs(0), erreurPrecedente(0),
    Kp(FILTER_ANGLE_KP), Kd(FILTER_ANGLE_KD), Ki(FILTER_ANGLE_KI)
{
}

float PIDFilterAngle::getFilteredValue(Angle erreur){
    sommeErreurs=sommeErreurs*FILTER_ANGLE_COEF+erreur;
    Angle proportionnel = erreur;
    Angle integrale = sommeErreurs;
    Angle derivee = erreur - erreurPrecedente;
    erreurPrecedente=erreur;
    return proportionnel*Kp
         + integrale*Ki
         + derivee*Kd;
}

void PIDFilterAngle::resetErrors(){
    sommeErreurs = 0;
    erreurPrecedente = 0;
}

float PIDFilterAngle::getKp()
{
    return Kp;
}

float PIDFilterAngle::getKi()
{
    return Ki;
}

float PIDFilterAngle::getKd()
{
    return Kd;
}

void PIDFilterAngle::setSettings(float p, float i, float d)
{
    Kp = p;
    Ki = i;
    Kd = d;
}
