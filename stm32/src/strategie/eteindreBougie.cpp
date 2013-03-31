#include "eteindreBougie.h"

EteindreBougie::EteindreBougie(int rotation, bool our, bool triggered)
{
    this->rotation = rotation;
    this->our = our;
    this->triggered = triggered;
}
virtual EteindreBougie::~EteindreBougie()
{
}
virtual int EteindreBougie::update() {
	throw "Not yet implemented";
}
