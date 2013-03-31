#include "lancerAscenseur.h"

LancerAscenseur::LancerAscenseur(int speed, Moteur* motor) : LowLevelAction(0)
{
    this->speed = speed;
    this->motor = motor;
}
virtual LancerAscenseur::~LancerAscenseur()
{
}
bool LancerAscenseur::update() {
	throw "Not yet implemented";
}
