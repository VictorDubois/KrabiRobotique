#include "pidFilterDistance.h"

PIDFilterDistance::PIDFilterDistance() :
    sommeErreurs(0), erreurPrecedente(0),
    Kp(FILTER_LINEAIRE_KP), Ki(FILTER_LINEAIRE_KI), Kd(FILTER_LINEAIRE_KD)
{
}

float PIDFilterDistance::getFilteredValue(Distance erreur){
    sommeErreurs=sommeErreurs*FILTER_LINEAIRE_COEF+erreur;
    Distance proportionnel = erreur;
    Distance integrale = sommeErreurs;
    Distance derivee = erreur - erreurPrecedente;
    erreurPrecedente=erreur;
    return proportionnel*Kp
         + integrale*Ki
         + derivee*Kd;
}

void PIDFilterDistance::resetErrors(){
    sommeErreurs = 0;
    erreurPrecedente = 0;
}

float PIDFilterDistance::getKp()
{
    return Kp;
}

float PIDFilterDistance::getKi()
{
    return Ki;
}

float PIDFilterDistance::getKd()
{
    return Kd;
}

void PIDFilterDistance::setSettings(float p, float i, float d)
{
    Kp = p;
    Ki = i;
    Kd = d;
}
