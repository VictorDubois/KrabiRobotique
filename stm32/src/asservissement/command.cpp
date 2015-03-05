#include "command.h"
#include "asservissement.h"

Vitesse Command::vitesse_lineaire_max = VITESSE_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Vitesse Command::vitesse_angulaire_max = VITESSE_ANGULAIRE_MAX; // en radian par nb_ms_between_updates
Acceleration Command::acceleration_lineaire = ACCELERATION_LINEAIRE_MAX; // en mm par nb_ms_between_updates
Acceleration Command::acceleration_angulaire = ACCELERATION_ANGULAIRE_MAX; // en radian par nb_ms_between_updates

bool Command::stop = false;
bool Command::limiter = false;

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

void Command::resetSpeeds()
{

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

void Command::limitSpeed(bool doitLimiter)
{
    Command::limiter = doitLimiter;
    //vitesseLinMax = 1;//TODO : mettre une valeur réaliste, ou bien sauvegarder la première valeure et la diviser
}

bool Command::getLimit(void)
{
    return Command::limiter;
}

bool Command::isNear(Position pos, float precision)
{
    Position vect = pos - Odometrie::odometrie->getPos().getPosition();

    return (vect.getNorme() < (int) precision);
}

bool Command::isLookingAt(Angle a, float precision)
{
    Angle diff = a - Odometrie::odometrie->getPos().angle;

    while(diff >= M_PI)
        diff -= 2.*M_PI;
    while(diff < -M_PI)
        diff += 2.*M_PI;

    return (fabs(diff) < precision);
}

bool Command::isLookingAt(Position pos, float precision)
{
    Position delta = pos - Odometrie::odometrie->getPos().getPosition();
    Angle angleVise = atan2(delta.getY(),delta.getX());
    Angle diff = angleVise - Odometrie::odometrie->getPos().angle;

    while(diff >= M_PI)
        diff -= 2.*M_PI;
    while(diff < -M_PI)
        diff += 2.*M_PI;

    return (fabs(diff) < precision);
}
