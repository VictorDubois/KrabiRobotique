#include "canonLances.h"
#define RAPPORT_TIR 0.35
#define RAPPORT_TIR_LOW 0.35
#define LOADER_ANGLE_PRECHARGE 165
#define LOADER_ANGLE_SHOOT 70

#if defined(STM32F10X_MD)  || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#elif defined(STM32F40_41xxx)
    #include "stm32f4xx_conf.h"
    #include "system_stm32f4xx.h"
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
#endif

#ifndef ROBOTHW
    #include <QDebug>
#endif

CanonLances* CanonLances::singleton = 0;

CanonLances* CanonLances::getSingleton()
{
    if (singleton==0)
        singleton = new CanonLances();

    return singleton;
}

//CanonLances::~CanonLances()
//{
//    servoCharge->shutDownServo();
//    delete moteurTir;
//    delete servoCharge;
//    delete canonLances;
//}

CanonLances::CanonLances()
{
#ifdef ROBOTHW
    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    moteurTir = new Moteur(TIM5,3,GPIOA,GPIO_Pin_2);
    //NOUVEAU CONSTRUCTEUR DE MOTEUR A DEFINIR, SANS LE PIN DE SENS (ici le sens est tjs le même)
    servoCharge = new Servo(timer1,1,0.01f, 0.11f);

    arm();
#endif
}


void CanonLances::shootAtWill()
{
#ifdef ROBOTHW
    moteurTir->tourne(RAPPORT_TIR);
#else
    qDebug() << "CanonLances shootAtWill";
#endif
}

void CanonLances::shootAtWillLow()
{
#ifdef ROBOTHW
    moteurTir->tourne(RAPPORT_TIR_LOW);
#else
    qDebug() << "CanonLances shootAtWillLow";
#endif
}

void CanonLances::stopShootAtWill()
{
#ifdef ROBOTHW
    moteurTir->tourne(0);
#else
    qDebug() << "CanonLances stopShootAtWill";
#endif
}

void CanonLances::arm()
{
#ifdef ROBOTHW
    servoCharge->goToAngle(LOADER_ANGLE_PRECHARGE);
#else
    qDebug() << "CanonLances arm";
#endif
}

void CanonLances::fire()
{
#ifdef ROBOTHW
    servoCharge->goToAngle(LOADER_ANGLE_SHOOT);
#else
    qDebug() << "CanonLances fire";
#endif
}
