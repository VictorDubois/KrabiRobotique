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
    
    ServosNumeriques::initClocksAndPortsGPIO();
    /*while(1) {
    allumerLED();
    ServosNumeriques::initUART(1000000);
    ServosNumeriques::sendMode();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setBaudRate(0x67, 13);
        eteindreLED();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setLedState(1, 13);
    for (int i = 0; i < 3000000; i++){ }
    allumerLED();
    ServosNumeriques::initUART(200000);
    ServosNumeriques::sendMode();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setBaudRate(0x67, 13);
        eteindreLED();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setLedState(1, 13);
    for (int i = 0; i < 3000000; i++){ }
    allumerLED();
    ServosNumeriques::initUART(19230);
    ServosNumeriques::sendMode();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setBaudRate(0x67, 13);
        eteindreLED();
    for (int i = 0; i < 3000000; i++){}
    ServosNumeriques::setLedState(1, 13);
    for (int i = 0; i < 3000000; i++){ }
    }*/
    
    allumerLED();
        for (int i = 0; i < 1000000; i++)
        {
        }
        
        eteindreLED();
        for (int i = 0; i < 3000000; i++)
        {
        }
        //ServosNumeriques::setBaudRate(0x67, 12);
        //ServosNumeriques::setLedState(1, 12);
        allumerLED();
        for (int i = 0; i < 30000; i++)
        {
        }
        eteindreLED();
        for (int i = 0; i < 30000; i++)
        {
        }
        //ServosNumeriques::setBaudRate(0x67, 13);
        //ServosNumeriques::setLedState(1, 13);
        for (int i = 0; i < 30000; i++)
        {
        }
        //ServosNumeriques::initUART(1000000);

        //ServosNumeriques::sendMode();
        allumerLED();
        for (int i = 0; i < 1000000; i++)
        {
        }
        
        eteindreLED();
        for (int i = 0; i < 3000000; i++)
        {
        }
    //ServosNumeriques::setBaudRate(0x67, 12);
    //ServosNumeriques::setLedState(1, 12);
        allumerLED();
        for (int i = 0; i < 30000; i++)
        {
        }
        eteindreLED();
        for (int i = 0; i < 30000; i++)
        {
        }
    //ServosNumeriques::setBaudRate(0x67, 13);
    //ServosNumeriques::setLedState(1, 13);
        for (int i = 0; i < 30000; i++)
        {
        }
        
    //ServosNumeriques::setLedState(1, 12);
    //ServosNumeriques::setMinimumAngle(0x0000, 11);
    for (int i = 0; i < 10000; i++)
    {
    }
    //ServosNumeriques::setMaximumAngle(0x03ff, 11);
        for (int i = 0; i < 1000000; i++)
        {
        }
        for (int i = 0; i < 1000000; i++)
        {
        }
    //ServosNumeriques::setLedState(1, 11);
/*
        //ServosNumeriques::moveToAtSpeed(0x0000, 0x0500, 12); // speed -0x0200 
        //ServosNumeriques::moveToAtSpeed(0x03ff, 0x0500, 12); // 0x07ff, 13);
        //ServosNumeriques::moveToAtSpeed(0x030, 0x0200, 12); // 0x07ff, 13);
        ServosNumeriques::moveToAtSpeed(0, 0x0600, 12); //AtSpeed(0x0200, 12);
        for (int j = 0; j < 1; j++)
        for (int i = 0; i < 3000000; i++)
        {
        }
        //ServosNumeriques::moveAtSpeed(0x0000, 12);
        ServosNumeriques::moveToAtSpeed(0x0100, 0x0200, 12); // 0x07ff, 13);*/
    for (int i = 0; i < 10000; i++)
    {
    }
    ServosNumeriques::initUART(19231);

    for (int i = 0; i < 10000; i++)
    {
    }
    ServosNumeriques::sendMode();
    for(int i = 0; i < 10000; i++)
    {
    }
    ServosNumeriques::setLedState(1, 12);
    ServosNumeriques::setLedState(1, 13);
    ServosNumeriques::setMaxTorque(0x03ff, MARTEAU_BAS_DROIT_ID);
    while(1)
    {/*
        ServosNumeriques::moveTo(0x100, 11);
        ServosNumeriques::moveTo(0x100, 12);
        ServosNumeriques::moveTo(0x100, 13);
        for (int i = 0; i < 1000000; i++)
        {
        }
        ServosNumeriques::moveTo(0x200, 11);
        ServosNumeriques::moveTo(0x200, 12);
        ServosNumeriques::moveTo(0x200, 13);*/
        for (int i = 0; i < 10000000; i++)
        {
        }
        ServosNumeriques::moveToAtSpeed(MARTEAU_BAS_DROIT_ENFONCE, 0x07ff, MARTEAU_BAS_DROIT_ID); // speed -0x0200 
        for (int i = 0; i < 1000000; i++)
        {
        }
        //ServosNumeriques::moveToAtSpeed(MARTEAU_HAUT_DROIT_ENFONCE, 0x0600, MARTEAU_HAUT_DROIT_ID); // speed -0x0200 
        for (int i = 0; i < 1000000; i++)
        {
        }
        /*ServosNumeriques::moveToAtSpeed(MARTEAU_BAS_GAUCHE_ENFONCE, 0x0200, MARTEAU_BAS_GAUCHE_ID); // speed -0x0200
        for (int i = 0; i < 1000000; i++)
        {
        }
        ServosNumeriques::moveToAtSpeed(MARTEAU_HAUT_GAUCHE_ENFONCE, 0x0200, MARTEAU_HAUT_GAUCHE_ID); // speed -0x0200 
        for (int i = 0; i < 10000000; i++)
        {
        }*/
        allumerLED();
        for (int i = 0; i < 10000000; i++)
        {
        }
        
        ServosNumeriques::moveToAtSpeed(MARTEAU_BAS_DROIT_RELEVE_ANGLE, 0x0200, MARTEAU_BAS_DROIT_ID); // speed -0x0200 
        for (int i = 0; i < 1000000; i++)
        {
        }
        //ServosNumeriques::moveToAtSpeed(MARTEAU_HAUT_DROIT_RELEVE_ANGLE, 0x0200, MARTEAU_HAUT_DROIT_ID); // speed -0x0200 
        for (int i = 0; i < 1000000; i++)
        {
        }
        /*
        ServosNumeriques::moveToAtSpeed(MARTEAU_BAS_GAUCHE_RELEVE_ANGLE, 0x0600, MARTEAU_BAS_GAUCHE_ID); // speed -0x0200
        for (int i = 0; i < 1000000; i++)
        {
        }
        ServosNumeriques::moveToAtSpeed(MARTEAU_HAUT_GAUCHE_RELEVE_ANGLE, 0x0600, MARTEAU_HAUT_GAUCHE_ID); // speed -0x0200 
        for (int i = 0; i < 10000000; i++)
        {
        }*/
        eteindreLED();
    }
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


