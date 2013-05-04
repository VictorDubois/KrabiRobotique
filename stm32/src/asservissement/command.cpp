#include "command.h"
#include "asservissement.h"

Vitesse Command::vitesse_lineaire_max = VITESSE_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Vitesse Command::vitesse_angulaire_max = VITESSE_ANGULAIRE_MAX; // en radian par nb_ms_between_updates
Acceleration Command::acceleration_lineaire = ACCELERATION_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Acceleration Command::acceleration_angulaire = ACCELERATION_ANGULAIRE_MAX; // en radian par nb_ms_between_updates

float abs(float x)
{
    return (x<0 ? -x : x);
}

float diffAngle(float a, float b)
{
    float t = a-b;
    float i = floor((t+M_PI)/2.f/M_PI);

    return t-i*2*M_PI;
}

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
