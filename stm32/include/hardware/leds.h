#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED


#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

#define LED_NUMBER 2

// allume ou éteint une LED
void allumerLED();
void eteindreLED();

void allumerLED2();
void eteindreLED2();

#ifndef ROBOTHW
    #define NB_LED 2
    static int ledIsOn[NB_LED];
    void turnLed(int led, bool turnOn);
    bool isLedOn(int led);
#endif

class Led
{
public:
    static void toggle(int index = 0);
    static void setOn(int index = 0);
    static void setOff(int index = 0);

private:
    static bool ledOn[LED_NUMBER];
};

#endif // LEDS_H_INCLUDED
