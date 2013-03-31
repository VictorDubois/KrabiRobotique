#include "actionnerAscenseur.h"

ActionnerAscenseur::ActionnerAscenseur()
{
#ifdef ROBOTHW
    this->servos[0] = NULL;
    this->servos[1] = NULL;
#endif
}
#ifdef ROBOTHW
ActionnerAscenseur::ActionnerAscenseur(Servo* servos[2])
{
    this->servos[0] = servos[0];
    this->servos[1] = servos[1];
}
#endif
ActionnerAscenseur::~ActionnerAscenseur()
{
}
bool ActionnerAscenseur::update() {
    return true;
}
