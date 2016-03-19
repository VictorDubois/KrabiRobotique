#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_tim.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_tim.h"
#endif


#include "initialisation.h"

#include "clock.h"

#ifdef ROBOTHW
Initialisation::Initialisation(PositionPlusAngle position) : start(position), tirette(0)
{
	rcd = 0;
	rcg = 0;
}
#else
#include <QDebug>
Initialisation::Initialisation(PositionPlusAngle position, bool yellow, Robot* robot) : start(position), robot(robot)
{
    setYellow(yellow);
}
#endif

void Initialisation::init()
{
    initClock();
    initGPIO();
    initRotaryEncoders();

#ifdef ROBOTHW
    odometrie = new Odometrie(rcg, rcd);

#else
    odometrie = new Odometrie(this->robot);
#endif

    strategie = new StrategieV2(isYellow());
/*
#ifdef ROBOTHW
    tirette->attendreRemise();
    tirette->attendreEnlevee();
    Clock::getInstance()->matchStart();
#endif
*/
    asservissement = new Asservissement(odometrie);

#ifdef ROBOTHW
    setYellow();
#endif

    if(!isYellow())
    {
        start = start.getSymetrical();
    }

    odometrie->setPos(start);
}

bool Initialisation::isYellow()
{
    return yellow;
}


Asservissement* Initialisation::getAsservissement()
{
    return asservissement;
}

Odometrie* Initialisation::getOdometrie()
{
    return odometrie;
}

StrategieV2* Initialisation::getStrategie()
{
    return strategie;
}

void Initialisation::setYellow(bool val)
{
    yellow = val;
}



