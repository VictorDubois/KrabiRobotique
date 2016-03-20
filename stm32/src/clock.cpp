#include "clock.h"

#include "asservissement/odometrie.h"
#include "asservissement/asservissement.h"
#include "hardware/tourelle.h"
#include "hardware/leds.h"

#ifndef ROBOTHW
    #include <QTimer>
#endif

#ifdef STM32F40_41xxx
    #define HW_CLOCK_SPEED 72000000   // 72Mhz
#else
    #define HW_CLOCK_SPEED 168000000  // 168Mhz
#endif

void Clock::everyTick()
{
}

void Clock::every5ms()
{
    #ifndef STM32F40_41xxx
        Odometrie::odometrie->update();
        Asservissement::asservissement->update();

        Tourelle::getSingleton()->update();
        //StrategieV2::update();
    #endif
}

void Clock::everySecond()
{
    Led::toggle(0);
}

Clock* Clock::getInstance()
{
    static Clock* instance = 0;
    if(instance == 0)
        instance = new Clock();
    return instance;
}

Clock::Clock()
{
    m_tickCount         = 0;
    m_last5msTick       = 0;
    m_matchStartTime    = 0;
    m_matchStarted      = false;

    #ifdef ROBOTHW
        *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1

        *((uint32_t *)(STK_LOAD_ADDR)) = (0.001*HW_CLOCK_SPEED*Clock::MS_PER_TICK)/8; // (doit etre inférieur à 0x00FFFFFF=16 777 215)
        /* (voir p190 de la doc) */

        NVIC_InitTypeDef SysTick_IRQ;

        SysTick_IRQ.NVIC_IRQChannel = SysTick_IRQn;
        SysTick_IRQ.NVIC_IRQChannelCmd = ENABLE;
        SysTick_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
        SysTick_IRQ.NVIC_IRQChannelSubPriority = 1;
        NVIC_Init(&SysTick_IRQ);
    #else
        /* Some trick with QTimer here */
    #endif
}

void Clock::tick()
{
    ++m_tickCount;

    everyTick();

    if((m_tickCount - m_last5msTick) * Clock::MS_PER_TICK > 5)
    {
        every5ms();
        m_last5msTick = m_tickCount;
    }

    if((m_tickCount - m_last5msTick) * Clock::MS_PER_TICK > 1000)
    {
        everySecond();
        m_last1sTick = m_tickCount;
    }
}

unsigned long Clock::elapsedSinceStartup() const
{
    return m_tickCount * Clock::MS_PER_TICK;
}

void Clock::matchStart()
{
    if(isMatchStarted())
        return;

    m_matchStarted = true;
    m_matchStartTime = m_tickCount;
}

unsigned long Clock::elapsedSinceMatchStart() const
{
    if(isMatchStarted())
        return (m_tickCount - m_matchStartTime) * Clock::MS_PER_TICK;
    return 0;
}

bool Clock::isMatchStarted() const
{
    return m_matchStarted;
}

bool Clock::hasMatchEnded() const
{
    return isMatchStarted() && (elapsedSinceMatchStart() >= Clock::MATCH_DURATION_MS);
}

unsigned int Clock::delay(unsigned int duration)
{
    unsigned int start = Clock::getInstance()->elapsedSinceStartup();

    while(duration > (Clock::getInstance()->elapsedSinceStartup()-start));

    return Clock::getInstance()->elapsedSinceStartup()-start;
}

extern "C" void SysTick_Handler()
{
    Clock::getInstance()->tick();
}
