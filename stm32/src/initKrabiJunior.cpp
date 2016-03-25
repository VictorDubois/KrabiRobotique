#include "initKrabiJunior.h"

#ifdef ROBOTHW
InitKrabiJunior::InitKrabiJunior() : Initialisation(PositionPlusAngle(Position(194, 1000), 0))
{
}
#else
#include <QDebug>
InitKrabiJunior::InitKrabiJunior(bool yellow, Robot* robot) : Initialisation(PositionPlusAngle(Position(194, 1000), 0), yellow, robot)
{
    qDebug() << "InitKrabi " << robot;
}
#endif

#ifdef ROBOTHW
void InitKrabiJunior::setYellow()
{
    yellow = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_RESET;
}
#endif

/** Initialisation roues codeuses **/
void InitKrabiJunior::initRotaryEncoders()
{
#ifdef ROBOTHW
//	rcd = new QuadratureCoderHandler(TIM4, GPIOB, GPIO_Pin_6, 	GPIOB, GPIO_Pin_7, GPIO_AF_TIM4, GPIO_PinSource6, GPIO_PinSource7);
//	rcg = new QuadratureCoderHandler(TIM1, GPIOA, GPIO_Pin_8, 	GPIOA, GPIO_Pin_9, GPIO_AF_TIM1, GPIO_PinSource8, GPIO_PinSource9);
#endif
}


void InitKrabiJunior::initClock()
{
#ifdef ROBOTHW
#ifdef STM32F40_41xxx
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
#endif
#endif
}

void InitKrabiJunior::initActionneurs()
{
#ifdef ROBOTHW
    ServosNumeriques::initClocksAndPortsGPIO();
    ServosNumeriques::initUART(1000000);
    ServosNumeriques::sendMode();

    /*Sensors* sensors = */Sensors::getSingleton();
    ServosNumeriques::setLedState(1, 12);
#endif
}

void InitKrabiJunior::initGPIO()
{
#ifdef ROBOTHW
    Tirette tirette(GPIOA, GPIO_Pin_10);

#ifdef STM32F40_41xxx
    GPIO_InitTypeDef GPIOStruct;

    GPIOStruct.GPIO_OType = GPIO_OType_PP;
    GPIOStruct.GPIO_Speed = GPIO_Speed_2MHz;

    /** Sharps **/
    GPIOStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5;
    GPIOStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIOStruct);

    GPIOStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIOStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIOStruct);

    GPIOStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIOStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIOStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIOStruct);

    /** LEDS choix strat **/
    GPIOStruct.GPIO_Pin = GPIO_Pin_9;
    GPIOStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIOStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIOStruct);

    /** LED verte **/
    GPIOStruct.GPIO_Pin = GPIO_Pin_12;
    GPIOStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIOStruct.GPIO_OType = GPIO_OType_PP;
    GPIOStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIOStruct);
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
#endif

#endif
}
