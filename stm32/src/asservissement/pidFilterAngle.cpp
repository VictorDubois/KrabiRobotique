#include "pidFilterAngle.h"

const float PIDFilterAngle::Kp = FILTER_ANGLE_KP;
const float PIDFilterAngle::Kd = FILTER_ANGLE_KD;
const float PIDFilterAngle::Ki = FILTER_ANGLE_KI;

PIDFilterAngle::PIDFilterAngle() :
    sommeErreurs(0),
    erreurPrecedente(0)
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
