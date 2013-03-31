#ifndef DEF_DIODE
#define DEF_DIODE

#include <Arduino.h>

class Diode
{
public:
    Diode(int diodePin);
    ~Diode();
    void off();
    void on();
    void set(bool setOn);

private:
    int pin;

};

#endif

