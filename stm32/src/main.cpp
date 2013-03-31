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
//QuadratureCoderHandler* roueDroite = new QuadratureCoderHandler(TIM2);
// test
  // QuadratureCoderHandler* roueGauche = new QuadratureCoderHandler(TIM2);


    ///// DEBUT TEST
    QuadratureCoderHandler* roueDroite = new QuadratureCoderHandler(TIM2);
    //roueDroite->getTickValue() pour obtenir les ticks.

    // QuadratureCoderHandler* roueGauche = new QuadratureCoderHandler(TIM2);
#define PSDFSD 8474576
    bool a = true;

    allumerLED(); // verte
    ServosNumeriques::initClocksAndPortsGPIO();
    ServosNumeriques::initUART(1000000);
    ServosNumeriques::sendMode();


    int packet[11];

    //while(1) {
    /*
        allumerLED2();
        allumerLED();
            packet[0] = (int)0xFF;
            packet[1] = (int)0xFF;
            packet[2] = (int)0x02;
            packet[3] = (int)AX12_WRITE_DATA_PARAMS+2; // 4
            packet[4] = (int)AX12_WRITE_DATA; // 3
            packet[5] = (int)AX12_LED; // 0x1f = 31
            packet[6] = (int)0x01;
            packet[7] = (int)(int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_LED + 0x01);
            for (int i = 0; i < 8; i++){
                ServosNumeriques_sendData(packet[i]);
    // Wait until the send buffer is cleared finishes
    //while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    //USART_SendData(USART3, (u16) packet[i]);
}
 //               ServosNumeriques_sendData(packet[i]);
        for (int i = 0 ; i < 847450 ; i++) {};
            eteindreLED();
            eteindreLED2();
        for (int i = 0 ; i < 847450 ; i++) {};
    //}*/
    /*    packet[0] = (int)0xFF;
        packet[1] = (int)0xFF;
        packet[2] = (int)0xfe;
        packet[3] = (int)AX12_WRITE_DATA_PARAMS+2; // 4
        packet[4] = (int)AX12_WRITE_DATA; // 3
        packet[5] = (int)AX12_LED; // 0x1f = 31
        packet[6] = (int)0x01;
        packet[7] = (int)(int8_t)~(0xfe + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_LED + 0x01);
        for (int i = 0; i < 8; i++) {
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, (u16) packet[i]);
    }
    for (int i = 0 ; i < 847450 ; i++) {}; */
/*        packet[0] = (int)0xFF;
        packet[1] = (int)0xFF;
        packet[2] = (int)0x02;
        packet[3] = (int)AX12_WRITE_DATA_PARAMS+2; // 4
        packet[4] = (int)AX12_WRITE_DATA; // 3
        packet[5] = (int)AX12_LED; // 0x1f = 31
        packet[6] = (int)0x01;
        packet[7] = (int)(int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_LED + 0x01);
        for (int i = 0; i < 8; i++) {
            ServosNumeriques::sendData(packet[i]);
    //while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    //USART_SendData(USART3, (u16) packet[i]);
    }
    for (int i = 0 ; i < 847450 ; i++) {};
        packet[6] = (int)0x00;
        packet[7] = (int)(int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_LED + 0x00);
        for (int i = 0; i < 8; i++) {
            ServosNumeriques::sendData(packet[i]);
    //while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    //USART_SendData(USART3, (u16) packet[i]);
    }
    ServosNumeriques::setLedState(1, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};
*/
//            ServosNumeriques_sendData(packet[i]);

    ServosNumeriques::setLedState(0, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};
    ServosNumeriques::setLedState(1, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};
    ServosNumeriques::setLedState(0, 0x02);

    for (int i = 0 ; i < 847450 ; i++) {};
    ServosNumeriques::setMinimumAngle(0x0000, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};
    ServosNumeriques::setMaximumAngle(0x03ff, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};


    ServosNumeriques::moveTo(0x0000, 0x02);
    for (int i = 0 ; i < 847450 ; i++) {};
    ServosNumeriques::moveAtSpeed(0x0200, 0x02);
    eteindreLED();
    for (int i = 0 ; i < 8474500 ; i++) {};
    ServosNumeriques::moveToAtSpeed(0x0200, 0x0200, 0x02);
    for (int i = 0 ; i < 8474500 ; i++) {};
    ServosNumeriques::moveToAtSpeed(0x0000, 0x0200, 0x02);
    for (int i = 0 ; i < 8474500 ; i++) {};
    ServosNumeriques::moveToAtSpeed(0x0200, 0x0200, 0x02);

    while(1) {}


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


