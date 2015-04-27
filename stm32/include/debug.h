#ifndef DEBUG_H
#define DEBUG_H

#include "servo.h"
#include "leds.h"

#if defined(STM32F10X_MD)  || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#elif defined(STM32F40_41xxx)
    #include "stm32f4xx_conf.h"
    #include "system_stm32f4xx.h"
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
#endif

#include "initialisation.h"
#include "actionneurs/servo.h"
#include "memory.h"
#include "servo.h"
#include "odometrie.h"
#include "asservissement.h"
#include "sensors.h"
#include "quadratureCoderHandler.h"
#include "roues.h"
#include "roue.h"
#include "strategieV2.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "leds.h"
#include "etape.h"
#include "dijkstra.h"
#include "brasLateraux.h"
//#include "container.h"
#ifdef REMOTE_ON
    #include "remote.h"
#endif

class Debug
{
    public:
        static void run();
        static void testServoAnalog();
        static void testSharps();
        static void testADCSampleF4();
        static void testADC_DMASampleF4();
        static void testQuadrature(QuadratureCoderHandler* rcg, QuadratureCoderHandler* rcd);
        static void testBrasLateraux();
        static void testContainer();
        static void testTirette(Tirette* t);
        static void testRemote();
        /*void testServoNum();
        void testPWM();*/
    protected:
    private:
        static int __ADCSampleF4_adc_convert();
        static void __ADCSampleF4_adc_configure();
        static void __ADC_DMASampleF4_init(void);
};

#endif // DEBUG_H
