#include "Sharp.h"

Sharp::Sharp(int sensorPin) : Sensor(sensorPin)
{
    Serial.print("Sharp created on PIN : ");
    Serial.print(sensorPin);
    Serial.print("\n");

    values = (int*) malloc(sizeof(int) * SHARP_MEAN_NUMBER);
    for(int i(0); i<SHARP_MEAN_NUMBER; i++)
        values[i] = 0;
}

Sharp::~Sharp()
{

}

void Sharp::update()
{
    for(int i(SHARP_MEAN_NUMBER-1); i>0; i--)
        values[i] = values[i-1];
    values[0] = analogRead(pin);

    int sum = 0;
    for(int i(SHARP_MEAN_NUMBER-1); i>0; i--)
        sum += values[i];

    if (sum/SHARP_MEAN_NUMBER >= SHARP_LIMIT)
        value = 1;
    else if (sum/SHARP_MEAN_NUMBER <= SHARP_LIMIT_DOWN)
        value = 0;

    //if (pin==A1)
        //Serial.println(value);
}
