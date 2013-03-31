#include "pidFilterDistance.h"

const float PIDFilterDistance::Kp = FILTER_LINEAIRE_KP;
const float PIDFilterDistance::Kd = FILTER_LINEAIRE_KD;
const float PIDFilterDistance::Ki = FILTER_LINEAIRE_KI;


PIDFilterDistance::PIDFilterDistance() :
    sommeErreurs(0),
    erreurPrecedente(0)
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
