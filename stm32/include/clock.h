#ifndef CLOCK_H
#define CLOCK_H

/**@brief Interuption appelée régulièrement par le microcontroleur
 * @see Clock::MS_PER_TICK
 */
extern "C" void SysTick_Handler();

class Clock
{
    protected:
        virtual void everyTick();
        virtual void every5ms();
        virtual void everySecond();

    public:
        static const unsigned long MS_PER_TICK        = 5;
        static const unsigned long MATCH_DURATION_MS  = 90*1000;

        static Clock* getInstance();

        unsigned long elapsedSinceStartup() const;

        void matchStart();
        unsigned long elapsedSinceMatchStart() const;

        bool isMatchStarted() const;
        bool hasMatchEnded() const;


    protected:
        Clock();

    private:
        void tick();

        friend void ::SysTick_Handler();

        unsigned long m_tickCount;
        unsigned long m_last5msTick;
        unsigned long m_last1sTick;

        unsigned long m_matchStartTime;
        bool m_matchStarted;
};

#endif // CLOCK_H
