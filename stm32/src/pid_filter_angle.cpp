#include "pid_filter_angle.h"

/*const float PIDFilterAngle::Kp = 1.;//15.0;//150.0;//30.0;//75.0;//150.0;
const float PIDFilterAngle::Ki = 0.2;//0.02;
const float PIDFilterAngle::Kd = 20.0;//12500.0;//1250.0;*/

const float PIDFilterAngle::Kp = 1.;//15.0;//150.0;//30.0;//75.0;//150.0;
const float PIDFilterAngle::Ki = 0.2;//0.02;
const float PIDFilterAngle::Kd = 40.0;//12500.0;//1250.0;

PIDFilterAngle::PIDFilterAngle() :
    sommeErreurs(0),
    erreurPrecedente(0)
{
}

float PIDFilterAngle::getFilteredValue(Angle erreur){
    sommeErreurs=sommeErreurs*0.83+erreur;
    Angle proportionnel = erreur;
    Angle integrale = sommeErreurs;
    Angle derivee = erreur - erreurPrecedente;
    erreurPrecedente=erreur;
    return proportionnel*Kp
         + integrale*Ki
         + derivee*Kd;
}
