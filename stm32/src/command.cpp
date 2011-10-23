#include "command.h"

float Command::vitesse_lineaire_max = VITESSE_LINEAIRE_MAX; // en mm par nb_ms_between_updates
float Command::vitesse_angulaire_max = VITESSE_ANGULAIRE_MAX; // en radian par nb_ms_between_updates
float Command::acceleration_lineaire = ACCELERATION_LINEAIRE_MAX; // en mm par nb_ms_between_updates
float Command::acceleration_angulaire = ACCELERATION_ANGULAIRE_MAX; // en radian par nb_ms_between_updates

Command::Command()
{
	Command* & c = Asservissement::asservissement->command;
       c = this;
}

Command::~Command()
{

}

