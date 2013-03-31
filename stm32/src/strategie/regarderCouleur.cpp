#include "regarderCouleur.h"

RegarderCouleur::RegarderCouleur(Sensors* sensors)
{
    this->sensors = sensors;
    this->isBlue = false;
}
RegarderCouleur::~RegarderCouleur()
{
}

bool RegarderCouleur::update() {

}
