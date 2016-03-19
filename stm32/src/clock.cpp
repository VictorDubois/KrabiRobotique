#include "clock.h"

#include "asservissement/odometrie.h"
#include "asservissement/asservissement.h"
#include "hardware/tourelle.h"
#include "hardware/leds.h"

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
