#include "command.h"
#include "asservissement.h"

Vitesse Command::vitesse_lineaire_max = VITESSE_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Vitesse Command::vitesse_angulaire_max = VITESSE_ANGULAIRE_MAX; // en radian par nb_ms_between_updates
Acceleration Command::acceleration_lineaire = ACCELERATION_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Acceleration Command::acceleration_angulaire = ACCELERATION_ANGULAIRE_MAX; // en radian par nb_ms_between_updates

bool Command::stop = false;

Command::Command()
{
    Command::stop = false;
}

Command::~Command()
{
}

bool Command::getStop(void)
{
    return Command::stop;
}

void Command::freinageDUrgence(bool doitFreiner)
{
    Command::stop = doitFreiner;
}

// est ce que la commande a fini ?
bool Command::fini() const
{
    return false;
}

