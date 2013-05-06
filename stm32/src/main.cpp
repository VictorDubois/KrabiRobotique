#include "stm32f10x_gpio.h"
#include "initialisation.h"
#include "memory.h"
#include "servo.h"
#include "odometrie.h"
#include "asservissement.h"
#include "sensors.h"
#include "quadratureCoderHandler.h"
#include "roues.h"
#include "roue.h"
#include "strategie.h"
#include "sharpSensor.h"
#include "ax12api.h"
#include "interfaceServosNumeriques.h"
#include "capteurCouleur.h"
#include "tirette.h"
#include "marteaux.h"
#include "leds.h"

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

/*
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
*/
    ///// DEBUT TEST

    // TEST CAPTEUR COULEUR
/*
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

 TIM_TIxExternalClockConfig(TIM2, TIM_TIxExternalCLK1Source_TI1ED, TIM_ICPolarity_Rising, 3);

 TIM_Cmd(TIM2, ENABLE);
while(1)
{
    TIM_SetCounter(TIM2, 0);

    for (int te = 0 ; te < 30000 ; te++);
    uint16_t ticks2 = TIM_GetCounter(TIM2);

    if (ticks2 > 2000)
    {
        allumerLED2();
    }
    else
    {
        eteindreLED2();
    }
    if (ticks2 < 40)
    {
        allumerLED();
    }
    else
    {
        eteindreLED();
    }
  //  for (int z = 0 ; z < 200 ; z++);
}

*/
    // SUPER TEST

    // roues codeuses
 //    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
 //   QuadratureCoderHandler roueCodeuseGauche(TIM4, GPIOD, GPIO_Pin_12, GPIOD, GPIO_Pin_13);
 //   QuadratureCoderHandler roueCodeuseDroite(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);

/*
 GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    initPinPourServoAnalog(GPIOE, GPIO_Pin_9); // 1 8
    initPinPourServoAnalog(GPIOE, GPIO_Pin_11); // 1 10
    initPinPourServoAnalog(GPIOE, GPIO_Pin_13); // 1 12
    initPinPourServoAnalog(GPIOE, GPIO_Pin_14); // 1 13

    */
/*
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

    initPinPourServoAnalog(GPIOB, GPIO_Pin_1);
    initPinPourServoAnalog(GPIOB, GPIO_Pin_8);
    initPinPourServoAnalog(GPIOB, GPIO_Pin_10);
    initPinPourServoAnalog(GPIOB, GPIO_Pin_11);
*/
/*
 //   Timer* timer2 = new Timer(TIM2, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
 //   Timer* timer3 = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
 //   Timer* timer4 = new Timer(TIM4, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
 //   Timer* timer4 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    PWMHandler* pwm1 = new PWMHandler(timer1, 1);
    PWMHandler* pwm2 = new PWMHandler(timer1, 2);
    PWMHandler* pwm3 = new PWMHandler(timer1, 3);
    PWMHandler* pwm4 = new PWMHandler(timer1, 4);


 //   initPinPourServoAnalog(GPIOA, GPIO_Pin_1);
 //   initPinPourServoAnalog(GPIOA, GPIO_Pin_2); // 1 6
//    initPinPourServoAnalog(GPIOA, GPIO_Pin_3); // 2 29
 //   Timer* timer5 = new Timer(TIM5, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
  //  PWMHandler* pwm5 = new PWMHandler(timer5, 2);
 //   PWMHandler* pwm6 = new PWMHandler(timer5, 3);
 //   PWMHandler* pwm7 = new PWMHandler(timer5, 4);

    // Met à disposition le timer
   // TIM_Cmd(TIM2, ENABLE);
int teserg = 0;
    while (true)
    {
*/

 /*       int ticks = roueCodeuseGauche.getTickValue();

        if (ticks > 0)
            allumerLED();
        else
            eteindreLED();
        if (ticks < 0)
            allumerLED2();
        else
            eteindreLED2();

ticks = roueCodeuseDroite.getTickValue();

      ticks = TIM_GetCounter(TIM2);
        TIM_SetCounter(TIM2, 0);
        if (ticks != 0)
        {
            allumerLED();
            allumerLED2();
        }

        else
        {
            eteindreLED();
             eteindreLED2();
        }
*/
/*
teserg++;

        pwm1->setDutyCycle((teserg%10)*0.02f);
        pwm2->setDutyCycle((teserg%10)*0.02f);
        pwm3->setDutyCycle((teserg%10)*0.02f);
        pwm4->setDutyCycle((teserg%10)*0.02f);
   //     pwm5->setDutyCycle((teserg%20)*0.05f);
  //     pwm6->setDutyCycle((teserg%20)*0.05f);
     //   pwm7->setDutyCycle((teserg%20)*0.05f);

        for (int i = 0 ; i < 2000000 ; i++);
    }
*/
    // TEST CAPTEURS
/*    uint8_t channels[1] = {10}; // ext 2 23, pc0
    uint16_t* data = AnalogSensor::initialiserADC(1, channels);



    SharpSensor sharpSensor(SharpSensor::FRONT, 10, data);
    LimitSwitchSensor finCourse(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD);

    while (true)
    {

        AnalogSensor::startConversion();
        sharpSensor.updateValue();

        finCourse.updateValue();

        if (sharpSensor.getValue().b)
            allumerLED();
        else
            eteindreLED();

        if (finCourse.getValue().b)
            allumerLED2();
        else
            eteindreLED2();

        for (int i = 0 ; i < 70000 ; i++);
    }
*/
// TEST SEERVOMOTEUR NUMERIQUE
/*
    allumerLED(); // verte
    servosNumeriques_initServosNumeriquesRCC();
    servosNumeriques_initGPIO();
    servosNumeriques_initUART(1000000);
    servosNumeriques_sendMode();

    eteindreLED(); // verte eteinte
    allumerLED2(); // orange allumee

    int8_t packet[8];
    int8_t id = 0xFF;
    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = id;
    packet[3] = AX12_WRITE_DATA_PARAMS+2; // 4
    packet[4] = AX12_WRITE_DATA; // 3
    packet[5] = AX12_LED;
    packet[6] = 0x01;
    packet[7] = ~(id + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_LED + 0x01);


    for (int i = 0; i < 8; i++)
        servosNumeriques_sendData(packet[i]);

eteindreLED2(); // orange eteinte
*/
/*
    packet[0] = (int8_t)0xFF;
    packet[1] = (int8_t)0xFF;
    packet[2] = (int8_t)0x02;
    packet[3] = (int8_t)AX12_WRITE_DATA_PARAMS+2; // 4
    packet[4] = (int8_t)AX12_WRITE_DATA; // 3
    packet[5] = (int8_t)AX12_GOAL_POSITION_H; // 0x1f = 31
    packet[6] = (int8_t)0x00;
    packet[7] = (int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_GOAL_POSITION_H + 0x00);


    for (int i = 0; i < 8; i++)
        servosNumeriques_sendData(packet[i]);


    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0x02;
    packet[3] = AX12_WRITE_DATA_PARAMS+2;
    packet[4] = AX12_WRITE_DATA;
    packet[5] = AX12_MOVING_SPEED_H;
    packet[6] = 0x00;
    packet[7] = (int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_MOVING_SPEED_H + 0x00);
    for (int i = 0; i < 8; i++)
        servosNumeriques_sendData(packet[i]);

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = 0x02;
    packet[3] = AX12_WRITE_DATA_PARAMS+2;
    packet[4] = AX12_WRITE_DATA;
    packet[5] = AX12_MOVING_SPEED_L;
    packet[6] = 0x00;
    packet[7] = (int8_t)~(0x02 + AX12_WRITE_DATA_PARAMS+2 + AX12_WRITE_DATA + AX12_MOVING_SPEED_L + 0x00);
    for (int i = 0; i < 8; i++)
        servosNumeriques_sendData(packet[i]);

    // wait some time
    for (int i = 0 ; i < 84745000 ; i++) {};

    eteindreLED2();
    allumerLED();

    servosNumeriques_receiveMode();
    for (int i = 0 ; i < 847450 ; i++);

    int16_t s = USART_ReceiveData(USART3);

    while (s != 0)
    {
        s = USART_ReceiveData(USART3);
        for (int i = 0 ; i < 847450 ; i++);
        allumerLED();
        for (int i = 0 ; i < 847450 ; i++);
        eteindreLED();
    }
    eteindreLED();
    eteindreLED2();

while(true);
*/

    // TEST LED BLINK
/*
    int tick = 0;
    while(1)
    {
        if (tick & 1 == 0)
        {
            allumerLED();
            eteindreLED2();
        }
        else
        {
            eteindreLED();
            allumerLED2();
        }

        for (int i = 0 ; i < 7000000; i++);
        tick++;
    }
    return 0;
*/


    // TEST SERVO
/*
    GPIO_InitTypeDef GPIO_InitStructure;

// tim2 ch 1 (ext1 4)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // tim3 ch 4 (ext1 16)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // tim3 ch 4 (ext1 20)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    Timer* timer = new Timer(TIM2, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);

    Servo* servo = new Servo(timer, 1);

    while (1)
    {
        servo->goToAngle(40);
        allumerLED();
        for (int i = 0 ; i < 7000000; i++);
        servo->goToAngle(180);
        eteindreLED();
        for (int i = 0 ; i < 7000000; i++);
    }
*/
   // test servo + roue codeuse

 /*      GPIO_InitTypeDef GPIO_InitStructure;

 //   QuadratureCoderHandler* qchRoue = new QuadratureCoderHandler(TIM3);

    // tim3 ch 4 (ext1 16)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // tim4 ch 3 (ext1 20)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    Timer* timer = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    Servo* servo = new Servo(timer, 4);



    while (1)
    {
        servo->goToAngle(40);
        for (int i = 0 ; i < 2000000; i++);

       int16_t ticks = qchRoue->getTickValue();
        if (ticks > 0)
            allumerLED();
        else
            eteindreLED();

        if (ticks < 0)
            allumerLED2();
        else
            eteindreLED2();

    }
*/

    // TEST ROUE CODEUSE
/*
    QuadratureCoderHandler* rcdroite = new QuadratureCoderHandler(TIM2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_1);
    QuadratureCoderHandler* rcgauche = new QuadratureCoderHandler(TIM3, GPIOA, GPIO_Pin_6, GPIOA, GPIO_Pin_7);
      while (1)
        {

            int16_t ticks = rcdroite->getTickValue();

            if (ticks > 0)
                allumerLED();
            else
                eteindreLED();

            if (ticks < 0)
                allumerLED2();
            else
                eteindreLED2();

           for (int i = 0 ; i < 100000; i++);
       }*/

    // TEST MOTEUR
/*
    Roues roues;

    while (1)
    {
        roues.droite.tourne(0.35f);
                roues.gauche.tourne(0.35f);
                for (int j = 0 ; j < 500000; j++);
    }
*/
/*
    Roues roues;

if (isBlue())
{
    for (int i = 0 ; i < 30; i++)
            {
                roues.droite.tourne(-0.015f*i);
                roues.gauche.tourne(-0.015f*i);
                for (int j = 0 ; j < 500000; j++);
            }

        while (1)
        {

            for (int i = 30 ; i > -30; i--)
            {
                roues.droite.tourne(-0.015f*i);
                roues.gauche.tourne(-0.015f*i);
                for (int j = 0 ; j < 400000; j++);
            }

            for (int i = -30 ; i < 30; i++)
            {
                roues.droite.tourne(-0.015f*i);
                roues.gauche.tourne(-0.015f*i);
                for (int j = 0 ; j < 400000; j++);
            }

           roues.droite.tourne(-0.45f);
           roues.gauche.tourne(-0.45f);
           for (int i = 0 ; i < 10000000; i++);
       }*/
/*
        while (1)
        {
                roues.droite.tourne(-0.3f);
                roues.gauche.tourne(-0.3f);
                for (int j = 0 ; j < 12000000; j++);

                roues.droite.tourne(0.3f);
                roues.gauche.tourne(0.3f);
                for (int j = 0 ; j < 12000000; j++);
        }


}
else
{
            for (int i = 5 ; i < 40; i++)
            {
                roues.droite.tourne(-0.015f*i);
                roues.gauche.tourne(-0.015f*i);
                for (int j = 0 ; j < 400000; j++);
            }

            roues.droite.tourne(-0.6f);
            roues.gauche.tourne(-0.6f);
            for (int j = 0 ; j < 10000000; j++);

            for (int i = 0 ; i < 15 ; i++)
            {
                roues.droite.tourne(-0.45f);
                roues.gauche.tourne(-0.03f*(15-i));
                for (int j = 0 ; j < 500000; j++);
            }

            roues.droite.tourne(-0.45f);
            roues.gauche.tourne(0.2f);
            for (int j = 0 ; j < 20000000; j++);

            for (int i = 0 ; i < 15 ; i++)
            {
                roues.droite.tourne(-0.45f);
                roues.gauche.tourne(-0.03f*i);
                for (int j = 0 ; j < 400000; j++);
            }

            roues.droite.tourne(-0.45f);
            roues.gauche.tourne(-0.45f);
            for (int j = 0 ; j < 15000000; j++);

            for (int i = 30 ; i >= 0; i--)
            {
                roues.droite.tourne(-0.015f*i);
                roues.gauche.tourne(-0.015f*i);
                for (int j = 0 ; j < 300000; j++);
            }


            while(1);
}*/

    // TEST MOTEUR + ROUE CODEUSE
/*
       Roues roues;
       QuadratureCoderHandler* qchRoueGauche = new QuadratureCoderHandler(TIM3);
       QuadratureCoderHandler* qchRoueDroite = new QuadratureCoderHandler(TIM2);

       while (1)
        {

           int16_t ticksGauche = qchRoueGauche->getTickValue();
            int16_t ticksDroite = qchRoueDroite->getTickValue();

            if (ticksDroite > 0)
                allumerLED();
            else
                eteindreLED();

            if (ticksDroite < 0)
                allumerLED2();
            else
                eteindreLED2();

            float rapportGauche = (float)ticksGauche/100.0f;
            float rapportDroite = (float)ticksDroite/100.0f;

            if (rapportGauche > 0.8f)
                rapportGauche = 0.8f;
            else if (rapportGauche < -0.8f)
                rapportGauche = -0.8f;

            if (rapportDroite > 0.8f)
                rapportDroite = 0.8f;
            else if (rapportDroite < -0.8f)
                rapportDroite = -0.8f;

           roues.droite.tourne(rapportDroite);
           roues.gauche.tourne(rapportGauche);
           for (int i = 0 ; i < 1000000; i++);
       }

       // test tirette

    while (1)
    {
        if (isTiretteEnlevee())
        {
            eteindreLED();
            allumerLED2();
        }
        else
        {
            allumerLED();
            eteindreLED2();
        }

        for (int i = 0 ; i < 300000 ; i++);
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
/*#ifdef CAPTEURS
    new Sensors();
#endif*/

 /*   GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    initPinPourServoAnalog(GPIOE, GPIO_Pin_9); // 1 8
    initPinPourServoAnalog(GPIOE, GPIO_Pin_11); // 1 10
    initPinPourServoAnalog(GPIOE, GPIO_Pin_13); // 1 12
    initPinPourServoAnalog(GPIOE, GPIO_Pin_14); // 1 13

    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
     TIM_CtrlPWMOutputs(TIM1, ENABLE);
    PWMHandler* pwm1 = new PWMHandler(timer1, 1);
    PWMHandler* pwm2 = new PWMHandler(timer1, 2);
    PWMHandler* pwm3 = new PWMHandler(timer1, 3);
    PWMHandler* pwm4 = new PWMHandler(timer1, 4);
    Roue* ascensseur = new Roue(TIM5, 3, GPIOA, uint16_t GPIO_Pin_2, GPIOD, GPIO_Pin_5);

    while (1)
    {
    pwm1->setDutyCycle(0.2f);
    pwm2->setDutyCycle(0.2f);
    pwm3->setDutyCycle(0.2f);
    pwm4->setDutyCycle(0.2f);


    ascensseur->tourne(0.5f);
    for (int i = 0 ; i < 200000 ; i++);
    }
*/
/*
    // initialisation des servomoteurs
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    Servo::initPin(GPIOE, GPIO_Pin_9);
    Servo::initPin(GPIOE, GPIO_Pin_11);
    Servo::initPin(GPIOE, GPIO_Pin_13);
    Servo::initPin(GPIOE, GPIO_Pin_14);

    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    Servo* porteGaucheAsc = new Servo(timer1, 1, 0.1f, 0.2f);
    Servo* porteGaucheAsc2 = new Servo(timer1, 2, 0.1f, 0.2f);
    Servo* porteGaucheAsc3 = new Servo(timer1, 3, 0.1f, 0.2f);
    Servo* porteGaucheAsc4 = new Servo(timer1, 4, 0.1f, 0.2f);

    int i = 0;
    while (1)
    {
        if (i%20 == 0)
        {
            porteGaucheAsc->goToAngle(0);
            porteGaucheAsc2->goToAngle(0);
            porteGaucheAsc3->goToAngle(0);
            porteGaucheAsc4->goToAngle(0);
            allumerLED2();
            eteindreLED();
        }
        else if (i%10 == 0)
        {
            porteGaucheAsc->goToAngle(180);
            porteGaucheAsc2->goToAngle(180);
            porteGaucheAsc3->goToAngle(180);
            porteGaucheAsc4->goToAngle(180);
            allumerLED();
            eteindreLED2();
        }

        for (int d = 0 ; d < 1000000 ; d++);
        i++;
    }*/
/*

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;//GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;//GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_10;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET);

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;//GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET);

    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP; //GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;//GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_SET);

int i = 0;
    while (1)
    {
        if (i%24 == 0)
        {
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
            GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_RESET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_RESET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_SET);
            allumerLED2();

        }
        else if (i%12 == 0)
        {
            eteindreLED2();
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET);
            GPIO_WriteBit(GPIOC, GPIO_Pin_10, Bit_SET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_2, Bit_SET);
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, Bit_RESET);

        }

        for (int d = 0 ; d < 1000000 ; d++);
        i++;
    }
*/

    ServosNumeriques::initClocksAndPortsGPIO();
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::initUART(19231);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::sendMode();
    for (int i = 0; i < 10000; i++);

 /*   while (1)
    {
       Marteaux::enfoncerBasDroit();
        Marteaux::enfoncerBasGauche();
        Marteaux::enfoncerHautDroit();
        Marteaux::enfoncerHautGauche();
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }

        eteindreLED();
        Marteaux::releverBasDroit();
        Marteaux::releverBasGauche();
        Marteaux::releverHautDroit();
        Marteaux::releverHautGauche();
        for (int i = 0; i < 6000000; i++)
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


    new Strategie(isBlue(), odometrie);
    Asservissement* asserv = new Asservissement(odometrie);  // On définit l'asservissement

/*
    CapteurCouleur capteur(TIM3, 1, GPIOA, GPIO_Pin_6);
    while (1)
    {
        int ticks = capteur.getTickValue();
        if (ticks > 0)
            allumerLED();
        else
            eteindreLED();
        if (ticks < 0)
            allumerLED2();
        else
            eteindreLED2();

        for (int i = 0 ; i < 2000000 ; i++);
    }
*/
  //  new CommandGoTo(destination);

  //  Servo::initTimer();     // A faire avant toute utilisation de servo

 /*   new Bras();
    Bras::bras->monterRateau();
       Bras::bras->fermerBalaiDroit();
       Bras::bras->fermerBalaiGauche();

    new Strategie(isBlue(),odometrie);

*/
    while(1);

    return 0;
}


