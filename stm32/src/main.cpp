
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
#include "ascenseur.h"
#include "pinces.h"
#include "roues.h"
#include "roue.h"
#include "strategieV2.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "leds.h"
#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))
#include "commandAllerA.h"
#include "etape.h"
#include "dijkstra.h"
#include "microSwitch.h"

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


#ifdef ALLOW_DEBUG
    //Debug::testRemote();
    //Debug::testContainer();
    //Debug::testBrasLateraux();
    //Debug::testADC_DMASampleF4();
    //Debug::testSharps();
#endif

    allumerLED();
    eteindreLED();
    allumerLED2();
    eteindreLED2();
    allumerLED();

    //Remote::getSingleton()->waitForConnection();


    ServosNumeriques::initClocksAndPortsGPIO();
    ServosNumeriques::initUART(19231);
    ServosNumeriques::sendMode();
/*<<<<<<< HEAD

for(int i=0; i<2000; i++)
=======

for(int i=0; i<2000; i++)
>>>>>>> 8a8fced824885f8d8ca4fba8900250501d6a0eab
    {

        Pinces::getSingleton()->fermerPinces();

        for(int j=0; j<15000000; j++);


        Pinces::getSingleton()->ouvrirPinces();

        for(int j=0; j<15000000; j++);
    }

for(int i=0; i<2000; i++)
    {

        allumerLED();

        for(int j=0; j<1000000; j++);


        eteindreLED();

        for(int j=0; j<1000000; j++);
    }
<<<<<<< HEAD
=======
//    #ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
//        //MicroSwitch microSwitchBas(GPIOA, GPIO_Pin_10);//Exemple, il n'y a pas de microswitch pour KJ...
//        //MicroSwitch microSwitchHaut(GPIOA, GPIO_Pin_10);
//    #endif
//    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
//        //MicroSwitch microSwitchBas(GPIOA, GPIO_Pin_10);
//        //MicroSwitch microSwitchHaut(GPIOA, GPIO_Pin_10);
//    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        MicroSwitch microSwitchBas(GPIOE, GPIO_Pin_3);
        MicroSwitch microSwitchHaut(GPIOE, GPIO_Pin_2);
    #endif

    //Test MicroSwitch
//    while(1){
//        if(microSwitchBas.ferme()||microSwitchHaut->ferme())
//        {
//            allumerLED();
//        }
//        else
//        {
//            eteindreLED();
//        }
//    }

>>>>>>> 8a8fced824885f8d8ca4fba8900250501d6a0eab*/

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

    // Initialisation des actionneurs 1
    #if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // H405
        //BrasLateraux::initBrasLateraux();
        //Container::getSingleton();
    #elif defined(STM32F10X_CL) // H107
        BrasLateraux::initBrasLateraux();
//        CanonLances* canon = CanonLances::getSingleton();
    #endif

#ifdef ALLOW_DEBUG
    //Debug::testBrasLateraux();
#endif

    //tirette.attendreRemise();
    //tirette.attendreEnlevee();

    #if defined(STM32F10X_CL)
        Remote::getSingleton();
    #endif

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
    Position pos(250,1000, isBlue());//1500, isBlue());
    PositionPlusAngle posPlusAngle(pos,0);
    if (!isBlue())
        posPlusAngle = PositionPlusAngle(pos,-M_PI);
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

