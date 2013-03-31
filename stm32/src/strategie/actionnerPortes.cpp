#include "actionnerPortes.h"

ActionnerPortes::ActionnerPortes(Servo* servos[2], bool close)
{
    this->close = close;
    this->servos = servos;
}
virtual ActionnerPortes::~ActionnerPortes()
{
}

bool ActionnerPortes::update() {
	throw "Not yet implemented";
}
