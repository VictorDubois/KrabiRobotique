#include "lancerAscenseur.h"

#define LIFTER_UPDATE_COUNT 10
#define LIFTER_HEIGHT 50
#define MOTOR_HEIGHT_PER_CYCLE 10

LancerAscenseur::LancerAscenseur(int speed, Moteur* motor) : LowLevelAction(0)
{
    this->speed = speed;
    this->motor = motor;
}
LancerAscenseur::~LancerAscenseur()
{
}
int LancerAscenseur::update() {
    if (status == 0)
        status = 1;

    if (status > LIFTER_UPDATE_COUNT) //If action is ended, stop motor and return true.
    {
#ifdef ROBOTHW
        motor->tourne(0);
#endif
        return 1;
    }

    if (status == 1) //If first call : send order.
    {
#ifdef ROBOTHW
        motor->tourne(LIFTER_HEIGHT/(MOTOR_HEIGHT_PER_CYCLE*speed));
#endif
    }
    status++; //Status is used as a count of calls to update
    return 0; //Action not ended so return false.

}
