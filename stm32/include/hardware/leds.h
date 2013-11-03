#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

#include "stm32f10x_gpio.h"
// allume ou éteint une LED
void allumerLED();
void eteindreLED();

void allumerLED2();
void eteindreLED2();

#ifndef ROBOTHW
#define NB_LED 2
static int ledIsOn[NB_LED];
static void turnLed(int led, bool turnOn);
bool isLedOn(int led);
#endif

#endif // LEDS_H_INCLUDED
