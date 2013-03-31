#include "actionnerPortes.h"

ActionnerPortes::ActionnerPortes(bool close)
{
    this->close = close;
    this->servos[0] = NULL;
    this->servos[1] = NULL;
}
ActionnerPortes::ActionnerPortes(Servo* servos[2], bool close)
{
    this->close = close;
    this->servos[0] = servos[0];
    this->servos[1] = servos[1];
}
ActionnerPortes::~ActionnerPortes()
{
}

bool ActionnerPortes::update() {

}
