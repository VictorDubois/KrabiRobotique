#include "actionnerAscenseur.h"

ActionnerAscenseur::ActionnerAscenseur(Servo* servos[2])
{
    this->servos = servos;
}
virtual ActionnerAscenseur::~ActionnerAscenseur()
{
}
bool ActionnerAscenseur::update() {
	throw "Not yet implemented";
}
