#include "stm32f10x_gpio.h"
#include "initialisation.h"
#include "memory.h"
#include "servo.h"
#include "odometrie.h"
#include "asservissement.h"
#include "sensors.h"
#include "quadratureCoderHandler.h"
#include "bras.h"
#include "strategie.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"

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

// allume ou éteint une LED
void allumerLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
#endif
}

void eteindreLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
}

// 2ème LED du stm h107 (LED jaune)
#ifdef STM32F10X_CL
void allumerLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
}
void eteindreLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
}
#endif


int main()
{


	*NVIC_CCR = *NVIC_CCR | 0x200; // Set STKALIGN in NVIC

    // On initialise les horloges
    Clk_Init();

    // Définit quelques horloges supplémentaires
    initAutresHorloges();

    // Appel de la fonction qui permet d'initialiser tous les PINS
    initialisationDesPIN();


    ///// DEBUT TEST
    QuadratureCoderHandler* roueDroite = new QuadratureCoderHandler(TIM2);
    //roueDroite->getTickValue() pour obtenir les ticks.

    // QuadratureCoderHandler* roueGauche = new QuadratureCoderHandler(TIM2);
#define PSDFSD 8474576
    bool a = true;

    allumerLED(); // verte
    servosNumeriques_initServosNumeriquesRCC();
    servosNumeriques_initGPIO();
    servosNumeriques_initUART();
    servosNumeriques_sendMode();

    eteindreLED(); // verte eteinte
    allumerLED2(); // orange allumee

    int8_t packet[7];
    /*packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0x00;
    packet[3] = AX12_WRITE_DATA;
    packet[4] = AX12_GOAL_POSITION_L;
    packet[5] = 0x00;
    packet[6] = ~(int8_t)(0x04 + AX12_WRITE_DATA + AX12_GOAL_POSITION_L + 0x00);
    for (int i = 0; i < 7; i++)
        servosNumeriques_sendData(packet[i]);*/

    // envoi de la position
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0x00;
    packet[3] = AX12_WRITE_DATA;
    packet[4] = AX12_GOAL_POSITION_L;
    packet[5] = 0x00;
    packet[6] = ~(int8_t)(0x04 + AX12_WRITE_DATA + AX12_GOAL_POSITION_L + 0x00);
    for (int i = 0; i < 7; i++)
        servosNumeriques_sendData(packet[i]);

    // wait some time
    for (int i = 0 ; i < 8474500 ; i++);

    eteindreLED2();
    allumerLED();

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0x00;
    packet[3] = AX12_WRITE_DATA;
    packet[4] = AX12_GOAL_POSITION_L;
    packet[5] = 0xff;
    packet[6] = ~(int8_t)(0x04 + AX12_WRITE_DATA + AX12_GOAL_POSITION_L + 0xff);
    for (int i = 0; i < 7; i++)
        servosNumeriques_sendData(packet[i]);

    // wait some time
    for (int i = 0 ; i < 8474500 ; i++);

    eteindreLED();
    eteindreLED2();

    while(1) // do not start anything else
    {

    }

    /*while (1)
    {


        if (a)
        {
            allumerLED2();
            eteindreLED();
        }
        else
        {
            allumerLED();
            eteindreLED2();
        }
        a = !a;
        for (int i = 0 ; i < 8474500 ; i++);


    }*/

    ///// FIN TEST

    unsigned int buffer = 0xffffffff;
/*
#ifdef POSITIONNEMENT

    // on attend que la tirette soit remise
    while(buffer)
    {
        buffer <<= 1;
        buffer |= isTiretteEnlevee();
    }

#endif

    // On allume une LED sur le STM avant que la tirette soit testé. Ainsi, tant que la tirette est détectée, on garde la led allumée
    allumerLED();

    // On boucle tant que la tirette est pas enlever avec 32 verification au cas ou il y ai du bruit
    buffer = 0xffffffff;
    while(buffer)
    {
        buffer <<= 1;
        buffer |= !isTiretteEnlevee();
    }
*/
    // On éteint la LED sur le STM pour indiqué que le code continue à s'executer après que la tirette est été débranchée.
    eteindreLED();

    // Une fois que la tirette est enlevée pour la 1ère fois, on lance le positionnement automatique
    #ifdef CAPTEURS
        new Sensors();
    #endif

    Odometrie* odometrie = new Odometrie(new QuadratureCoderHandler(TIM1), new QuadratureCoderHandler(TIM2));

    new Asservissement(odometrie);  // On définit l'asservissement

    Servo::initTimer();     // A faire avant toute utilisation de servo

  /*   new Bras();
   Bras::bras->monterRateau();
    Bras::bras->fermerBalaiDroit();
    Bras::bras->fermerBalaiGauche();*/

    new Strategie(isBlue(),odometrie);


    while(1);

    return 0;
}


