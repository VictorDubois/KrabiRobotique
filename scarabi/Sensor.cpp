#include "Sensor.h"

Sensor::Sensor(int sensorPin)
{
    pin = sensorPin;
    value = 0;

    pinMode(sensorPin, INPUT);
}

Sensor::~Sensor()
{
    //dtor
}

int Sensor::getValue()
{
    return value;
}


void Sensor::update()
{
}
