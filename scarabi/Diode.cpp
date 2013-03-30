#include "Diode.h"

Diode::Diode(int diodePin)
{
    pin = diodePin;
    pinMode(pin,OUTPUT);
    Serial.println("Diode created !");
}

Diode::~Diode()
{

}

void Diode::set(bool setOn)
{
    if (setOn)
        on();
    else
        off();
}

void Diode::off()
{
    digitalWrite(pin,LOW);
}

void Diode::on()
{
    digitalWrite(pin,HIGH);
}

