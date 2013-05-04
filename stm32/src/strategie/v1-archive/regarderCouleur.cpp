#include "regarderCouleur.h"

RegarderCouleur::RegarderCouleur(Sensors* sensors) : LowLevelAction(0)
{
    this->sensors = sensors;
}
RegarderCouleur::~RegarderCouleur()
{
}

int RegarderCouleur::update() {

    if(1)//if (sensors.getIsBlue() == true) //If sensors says it's blue, status to return is 1. Else status = 2
        status = 1;
    else
        status = 2;
    return status; // return the value we got
}
