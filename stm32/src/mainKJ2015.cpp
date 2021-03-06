
#define STM32F4
#if defined(STM32F10X_MD)  || defined(STM32F10X_CL)
//#ifdef STM32F1
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
#include "bras.h"
#include "brak.h"
#include "roues.h"
#include "roue.h"
#include "strategieV2.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "canonLances.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "leds.h"
#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))
#include "marteaux.h"
#include "commandAllerA.h"
#include "etape.h"
#include "dijkstra.h"

#define ALLOW_DEBUG
#ifdef ALLOW_DEBUG
    #include "debug.h"
#endif

#define POSITIONNEMENT

#define DISABLE_TIRETTE


#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

// Dit si on est du coté bleu
bool isBlue() // = ROUGE
{
#ifdef STM32F40_41xxx // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_RESET;
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    return GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_RESET;
#endif
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_RESET;
#endif
}

// Dit si la tirette est enlevée
/*bool isTiretteEnlevee()
{
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == Bit_SET;
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    return GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == Bit_SET;
#endif
}

void initPinPourServoAnalog(GPIO_TypeDef* GPIOx, uint16_t pinX)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pinX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}
*/

int main()
{
    #if defined(STM32F10X_MD) || defined(STM32F10X_CL)
        *NVIC_CCR = *NVIC_CCR | 0x200; // Set STKALIGN in NVIC
    #else
        SystemInit(); // Appelée implicitement ?
    #endif

    // On initialise les horloges
    Clk_Init();

    // Définit quelques horloges supplémentaires
    initAutresHorloges();

    // Appel de la fonction qui permet d'initialiser tous les PINS
    initialisationDesPIN();

    Remote::log("Init");

#ifdef ALLOW_DEBUG
    //Debug::testRemote();
    //Debug::testContainer();
    //Debug::testBrasLateraux();
    //Debug::testADC_DMASampleF4();
    //Debug::testSharps();
#endif

//    UartDebug::initClocksAndPortsGPIO();
//    UartDebug::init(19200);
//    UartDebug::sendData(0);
//    UartDebug::sendData(1);
//    UartDebug::sendData(2);
//    UartDebug::sendData(10);
//    UartDebug::sendData(11);
//    UartDebug::sendData(12);
//    UartDebug::sendData(20);
//    UartDebug::sendData(21);
//    UartDebug::sendData(22);
//    UartDebug::sendData(30);
//    UartDebug::sendData(31);
//    UartDebug::sendData(32);
//    UartDebug::sendData(40);
//    UartDebug::sendData(41);
//    UartDebug::sendData(42);
//    UartDebug::sendData(50);
//    UartDebug::sendData(51);
//    UartDebug::sendData(52);

    ServosNumeriques::initClocksAndPortsGPIO();
    ServosNumeriques::initUART(1000000);//19230
    ServosNumeriques::sendMode();

    ServosNumeriques::changeContinuousRotationMode(21, true);
    ServosNumeriques::changeContinuousRotationMode(18, true);
    ServosNumeriques::moveAtSpeed(0x03fe, 21, true);
    ServosNumeriques::moveAtSpeed(0x0280, 18);
    for(int i = 0 ; i < 60 * 1000000 ; i++){}
//    ServosNumeriques::moveAtSpeed(0x03fe, 21);
//    ServosNumeriques::moveAtSpeed(0x0300, 18, true);
//    for(int i = 0 ; i < 2 * 1000000 ; i++){}
//    ServosNumeriques::moveAtSpeed(0x0, 21, true);
//    ServosNumeriques::moveAtSpeed(0x0, 18);
//    ServosNumeriques::changeContinuousRotationMode(18, false);
//    ServosNumeriques::changeContinuousRotationMode(21, false);
    ServosNumeriques::changeContinuousRotationMode(21,true);
    ServosNumeriques::changeContinuousRotationMode(18, true);
    //ServosNumeriques::moveAtSpeed(0x03fe, 21, true);
    for(int i = 0; i < 5 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(21, false);
    //ServosNumeriques::changeContinuousRotationMode(18, true);
    ServosNumeriques::moveAtSpeed(0x0300, 18);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(18, false);
    //ServosNumeriques::changeContinuousRotationMode(21,true);
    //ServosNumeriques::moveAtSpeed(0x03fe, 21, true);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(21, false);
    //ServosNumeriques::changeContinuousRotationMode(18, true);
    ServosNumeriques::moveAtSpeed(0x0300, 18);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(18, false);
    //ServosNumeriques::changeContinuousRotationMode(21,true);
    ServosNumeriques::moveAtSpeed(0x03fe, 21, true);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(21, false);
    //ServosNumeriques::changeContinuousRotationMode(18, true);
    ServosNumeriques::moveAtSpeed(0x0300, 18);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(18, false);
    //ServosNumeriques::changeContinuousRotationMode(21,true);
    ServosNumeriques::moveAtSpeed(0x03fe, 21, true);
    for(int i = 0; i < 10 * 1000000; i++){}
    //ServosNumeriques::changeContinuousRotationMode(21, false);
    //ServosNumeriques::changeContinuousRotationMode(18, true);
    ServosNumeriques::moveAtSpeed(0x0300, 18);
    for(int i = 0; i < 10 * 1000000; i++){}
    ServosNumeriques::changeContinuousRotationMode(18, false);
    ServosNumeriques::changeContinuousRotationMode(21, false);

    /*ServosNumeriques::changeContinuousRotationMode(13, false);

    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x03ff, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x03ff, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff

    ServosNumeriques::changeContinuousRotationMode(13, true);

    ServosNumeriques::moveAtSpeed(0x02ff, 13);
    ServosNumeriques::moveAtSpeed(0x0, 13);
    ServosNumeriques::moveAtSpeed(0x02ff + 1024, 13);
    ServosNumeriques::moveAtSpeed(0x0, 13);
    ServosNumeriques::moveAtSpeed(0x02ff, 13);
    ServosNumeriques::moveAtSpeed(0x0, 13);
    ServosNumeriques::moveAtSpeed(0x02ff, 13, true);
    ServosNumeriques::moveAtSpeed(0x0, 13);

    ServosNumeriques::changeContinuousRotationMode(13, false);

    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x03ff, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x03ff, 13); // position min : 0x0000, position max : 0x03ff
    ServosNumeriques::moveTo(0x0, 13); // position min : 0x0000, position max : 0x03ff*/

    #ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
        Tirette tirette(GPIOA, GPIO_Pin_10);
    #endif
    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        Tirette tirette(GPIOA, GPIO_Pin_10);
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        Tirette tirette(GPIOE, GPIO_Pin_5);
    #endif

#ifdef ALLOW_DEBUG
    //Debug::testTirette(&tirette);
#endif

    //waitServoNumeriquenitialisation des actionneurs 1
    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // H405
        BrasLateral::initBrasLateraux();
        Container::getSingleton();
    #elif defined(STM32F10X_CL) // H107
        BrasLateral::initBrasLateraux();
//        CanonLances* canon = CanonLances::getSingleton();
    #endif

#ifdef ALLOW_DEBUG
    //Debug::testBrasLateraux();
#endif



    Remote::getSingleton();
    tirette.attendreRemise();
    tirette.attendreEnlevee();
    // Initialisation des actionneurs 2
    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // H405

    #elif defined(STM32F10X_CL) // H107
//        Brak* bracquemart = Brak::getSingleton();
        Sensors* sensors = Sensors::getSingleton();
        ServosNumeriques::setLedState(1, 12);
    #endif



    #ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
        QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOB, GPIO_Pin_6, GPIOB, GPIO_Pin_7, GPIO_AF_TIM4 ,GPIO_PinSource6, GPIO_PinSource7);
        QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM1, GPIOA, GPIO_Pin_8, GPIOA, GPIO_Pin_9, GPIO_AF_TIM1 ,GPIO_PinSource8, GPIO_PinSource9);
    #endif
    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOB, GPIO_Pin_6, GPIOB, GPIO_Pin_7);
        QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM1, GPIOA, GPIO_Pin_8, GPIOA, GPIO_Pin_9);
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOD, GPIO_Pin_12, GPIOD, GPIO_Pin_13);
        GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
        QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
    #endif

    #ifdef ALLOW_DEBUG
        //Debug::testQuadrature(rcg, rcd);
    #endif


// Pour la v1 :
//    QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
 //   QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
    Odometrie* odometrie = new Odometrie(rcg, rcd);
    Position pos(200,1850, isBlue());//1500, isBlue());
    PositionPlusAngle posPlusAngle(pos,-M_PI/2);
    if (!isBlue())
        posPlusAngle = PositionPlusAngle(pos,-M_PI/2);
    odometrie->setPos(posPlusAngle);

    StrategieV2* strat = new StrategieV2(isBlue());
    Asservissement* asserv = new Asservissement(odometrie);

/*
    CommandAllerA* command = new CommandAllerA(Position(1000,230), false);
    command->update();
    asserv->setCommandSpeeds(command);
*/
    while(1);

    return 0;
}

