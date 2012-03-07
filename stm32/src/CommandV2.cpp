#include "CommandV2.h"



CommandV2::CommandV2() :
    Command(),      //Permet d'indiquer à l'asservicement l'adresse de cette instance
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0),
    fini(false)
{
}

CommandV2::~CommandV2()
{
       Command* & c = Asservissement::asservissement->command;
       c = NULL;
}

float CommandV2::getLinearSpeed()
{
	return vitesse_lineaire_a_atteindre;
}

Angle CommandV2::getAngularSpeed()
{
	return vitesse_angulaire_a_atteindre;
}


bool CommandV2::destinationAtteinte()
{
    return fini;
}

void CommandV2::goTo(Position position)
{
    fini = false;
    destination = position;
}
