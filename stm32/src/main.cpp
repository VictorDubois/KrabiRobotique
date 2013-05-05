#include "stm32f10x_gpio.h"
#include "initialisation.h"
#include "memory.h"
#include "servo.h"
#include "odometrie.h"
#include "asservissement.h"
#include "sensors.h"
#include "quadratureCoderHandler.h"
#include "bras.h"
#include "roues.h"
#include "roue.h"
#include "strategieV2.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "leds.h"
#include "marteaux.h"

#define POSITIONNEMENT

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

// Dit si on est du coté bleu
bool isBlue()
{
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == Bit_SET;
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    return GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == Bit_SET;
#endif
}

// Dit si la tirette est enlevée
bool isTiretteEnlevee()
{
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == Bit_SET;
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

int main()
{
    *NVIC_CCR = *NVIC_CCR | 0x200; // Set STKALIGN in NVIC

    // On initialise les horloges
    Clk_Init();

    // Définit quelques horloges supplémentaires
    initAutresHorloges();

    // Appel de la fonction qui permet d'initialiser tous les PINS
    initialisationDesPIN();
    
    /*ServosNumeriques::initClocksAndPortsGPIO();
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::initUART(19231);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::sendMode();*/
    /*
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MBD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MBG_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MHD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MHG_ID);
        allumerLED();
        for (int i = 0; i < 10000000; i++)
        {
        }
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MBD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MBG_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MHD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MHG_ID);
        eteindreLED();
        for (int i = 0; i < 10000000; i++)
        {}
        */
    /*
    while(1)
    {
        
    
        //Marteaux::enfoncerBasDroit(); 
        Marteaux::enfoncerBasGauche(); 
        //Marteaux::enfoncerHautDroit(); 
        //Marteaux::enfoncerHautGauche(); 
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }
        
        eteindreLED();
        //Marteaux::releverBasDroit();
        Marteaux::releverBasGauche(); 
        //Marteaux::releverHautDroit(); 
        //Marteaux::releverHautGauche(); 
        for (int i = 0; i < 6000000; i++)
        {
        }
    
        //arteaux::enfoncerBasDroit(); 
        Marteaux::enfoncerBasGauche(); 
        //Marteaux::enfoncerHautDroit(); 
        //Marteaux::enfoncerHautGauche(); 
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }
        
        eteindreLED();
        //Marteaux::releverBasDroit();
        Marteaux::releverBasGauche(); 
        //Marteaux::releverHautDroit(); 
        //arteaux::releverHautGauche(); 
        for (int i = 0; i < 13000000; i++)
        {
        }
        
        eteindreLED();
        Marteaux::rangerBasDroit();
        Marteaux::rangerBasGauche(); 
        Marteaux::rangerHautDroit(); 
        Marteaux::rangerHautGauche(); 
        for (int i = 0; i < 10000000; i++)
        {
        }
       
    }
    */
    // test fdc :
    /*
    LimitSwitchSensor* fdc1 = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD);
    LimitSwitchSensor* fdc2 = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOD);
    while(1)
    {
        fdc1->updateValue();
        fdc2->updateValue();
        if (fdc1->getValue().b)
            allumerLED();
        else    
            eteindreLED();
        if (fdc2->getValue().b)
            allumerLED2();
        else    
            eteindreLED2();
        for (int i = 0; i < 10000; i++)
        {
        }
    }*/
    /*
    uint8_t channels[10] = {9,8,10,11,12,13,14,15,5,4};
    uint16_t* data = AnalogSensor::initialiserADC(10, channels);
    int nbSharp = 10;
    SharpSensor** sharps = new SharpSensor*[nbSharp];
    sharps[0] = new SharpSensor(SharpSensor::FRONT, 9, data);
    sharps[1] = new SharpSensor(SharpSensor::FRONT_LEFT, 8, data);
    sharps[2] = new SharpSensor(SharpSensor::FRONT_RIGTH, 10, data);
    sharps[3] = new SharpSensor(SharpSensor::LEFT, 11, data);
    sharps[4] = new SharpSensor(SharpSensor::RIGTH, 12, data);
    sharps[5] = new SharpSensor(SharpSensor::BACK, 13, data);
    sharps[6] = new SharpSensor(SharpSensor::BACK, 14, data);
    sharps[7] = new SharpSensor(SharpSensor::BACK, 15, data);
    sharps[8] = new SharpSensor(SharpSensor::BACK, 5, data);
    sharps[9] = new SharpSensor(SharpSensor::BACK, 4, data);
    
    while(1)
    {
        AnalogSensor::startConversion();
        //allumerLED2();
        for (int i = 0; i < 10; i++) 
        {
            sharps[i]->updateValue();
        }
        bool allume = false;
        for (int i = 0; i < 10; i++)
        {
            if (sharps[i]->getValue().b)
            {
                allume = true;
            }
        }
        if (allume) {
            allumerLED();
        }
        else {
            eteindreLED();
        }
        for (int i = 0; i < 1000; i++)
        {
        }
        eteindreLED2();
        for (int i = 0; i < 1000; i++)
        {
        }
    }*/
    
    Tirette tirette(GPIOE, GPIO_Pin_5);
    tirette.attendreEnlevee();
// pour la v2 :

    QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOD, GPIO_Pin_12, GPIOD, GPIO_Pin_13);
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
    QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);

// Pour la v1 :
//    QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
 //   QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
    Odometrie* odometrie = new Odometrie(rcg, rcd);
    Position pos(270,560);
    PositionPlusAngle posPlusAngle(pos,0.0f);
    odometrie->setPos(posPlusAngle);


    Asservissement* asserv = new Asservissement(odometrie);  // On définit l'asservissement
    
    StrategieV2* strat = new StrategieV2();


    while(1);

    return 0;
}


