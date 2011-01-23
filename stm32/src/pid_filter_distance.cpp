#include "pid_filter_distance.h"

const float PIDFilterDistance::Kp = 0.00123076923*5.;
const float PIDFilterDistance::Ki = 0.00123076923;
const float PIDFilterDistance::Kd = 0.00123076923*200.;//0.0307692308;

PIDFilterDistance::PIDFilterDistance() :
    sommeErreurs(0),
    erreurPrecedente(0)
{
}

float PIDFilterDistance::getFilteredValue(Distance erreur){
    sommeErreurs=sommeErreurs*0.83+erreur;
    Distance proportionnel = erreur;
    Distance integrale = sommeErreurs;
    Distance derivee = erreur - erreurPrecedente;
    erreurPrecedente=erreur;
    return proportionnel*Kp
         + integrale*Ki
         + derivee*Kd;
}
