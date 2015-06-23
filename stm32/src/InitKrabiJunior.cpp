#include "InitKrabiJunior.h"

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

    Sensors* sensors = Sensors::getSingleton();
    ServosNumeriques::setLedState(1, 12);
#endif
}

void InitKrabiJunior::initGPIO()
{
#ifdef ROBOTHW
    Tirette tirette(GPIOA, GPIO_Pin_10);

    QuadratureCoderHandler* rcd = new QuadratureCoderHandler(TIM4, GPIOB, GPIO_Pin_6, GPIOB, GPIO_Pin_7, GPIO_AF_TIM4 ,GPIO_PinSource6, GPIO_PinSource7);
    QuadratureCoderHandler* rcg = new QuadratureCoderHandler(TIM1, GPIOA, GPIO_Pin_8, GPIOA, GPIO_Pin_9, GPIO_AF_TIM1 ,GPIO_PinSource8, GPIO_PinSource9);
#endif
}
