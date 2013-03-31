#include "actionnerAscenseur.h"

ActionnerAscenseur::ActionnerAscenseur()
{
    this->servos[0] = NULL;
    this->servos[1] = NULL;
}
ActionnerAscenseur::ActionnerAscenseur(Servo* servos[2])
{
    this->servos[0] = servos[0];
    this->servos[1] = servos[1];
}
ActionnerAscenseur::~ActionnerAscenseur()
{
}
bool ActionnerAscenseur::update() {

}
