#ifndef DEF_SHARP
#define DEF_SHARP

#include "Sensor.h"
#include "DiodeMgr.h"
#include <Arduino.h>

#define SHARP_LIMIT 350
#define SHARP_LIMIT_DOWN 300
#define SHARP_MEAN_NUMBER 8

class Sharp : public Sensor
{
public:
    Sharp(int sensorPin);
    ~Sharp();
    void update();

private:
    int* values;

};

#endif
