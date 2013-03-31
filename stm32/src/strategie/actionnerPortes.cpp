#include "actionnerPortes.h"

ActionnerPortes::ActionnerPortes(bool close)
{
    this->close = close;
#ifdef ROBOTHW
    this->servos[0] = NULL;
    this->servos[1] = NULL;
#endif
}
#ifdef ROBOTHW
ActionnerPortes::ActionnerPortes(Servo* servos[2], bool close)
{
    this->close = close;
    this->servos[0] = servos[0];
    this->servos[1] = servos[1];
}
#endif
ActionnerPortes::~ActionnerPortes()
{
}

bool ActionnerPortes::update() {

}
