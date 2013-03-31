#include "regarderCouleur.h"

RegarderCouleur::LowLevelAction(Sensors* sensors = NULL)
{
    this->sensors = sensors;
}
RegarderCouleur::~LowLevelAction()
{
}

virtual bool RegarderCouleur::update() {
    throw "not implemented yet";
}
