#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
public:
    Sensor(int sensorPin);
    virtual ~Sensor();

    int getValue();
    void update();
protected:
    int value, pin;
};

#endif // SENSOR_H
