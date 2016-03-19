#ifndef CLOCK_H
#define CLOCK_H

/**
 * @brief Interuption appelée régulièrement par le microcontroleur
 * @see Clock::MS_PER_TICK
 */
extern "C" void SysTick_Handler();

/**
 * @brief This singleton class provides a high-level interface for timey-winey stuff in pseudo-real time.
 * @see getInstance
 */
class Clock
{
    protected:
        /**
         * @brief This function is called every tick of the internal clock.
         */
        virtual void everyTick();
        /**
         * @brief This function is called approximatively every 5ms.
         *
         * Important note: if Clock::MS_PER_TICK is not a divisor of 5ms, the actual delay will be the closest superior multiple of
         * Clock::MS_PER_TICK, and the errors are NOT compensated for from one tick to the other
         * (i.e. if the delay between call N and call N+1 is 7ms, the delay between calls N+1 and N+2 will NOT be 3ms.
         * @see everyTick MS_PER_TICK
         */
        virtual void every5ms();
        /**
         * @brief This function is called approximatively every second.
         *
         * Important note: the same restrictions than every5ms apply here (but should be less noticeable).
         * @see every5ms everyTick MS_PER_TICK
         */
        virtual void everySecond();

    public:
        /**
         * SysTick_Handler() is called at regular inteval by the microcontroler, but 'regular' might mean different things
         * depending on the hardware or the low-level configuration. This constant 'fixes' the Clock so we might use pseudo-real
         * time instead of cycles.
         */
        static const unsigned long MS_PER_TICK        = 5;
        /**
         * The duration of a match, in ms.
         */
        static const unsigned long MATCH_DURATION_MS  = 90*1000;

        /**
         * @return The global Clock instance.
         */
        static Clock* getInstance();

        /**
         * @return The time elapsed since the clock was initialised, in ms.
         */
        unsigned long elapsedSinceStartup() const;

        /**
         * @brief Starts the match timer. Does nothing if already called before.
         */
        void matchStart();

        /**
         * @return The time elapsed since the match started, in ms, or 0 if the match hasn't started yet.
         */
        unsigned long elapsedSinceMatchStart() const;

        /**
         * @brief Returns true if the match was declared as 'started'.
         * @see matchStart hasMatchEnded
         */
        bool isMatchStarted() const;

        /**
         * @brief Returns true if the match has ended.
         *
         * A match is considered 'ended' if more than Clock::MATCH_DURATION_MS ms has gone by since the first call to matchStart().
         * @see matchStart Clock::MATCH_DURATION_MS
         */
        bool hasMatchEnded() const;

        /**
         * @brief Provides an active pause
         *
         * This functions 'waits' for the duration given in parameter. Note it CANNOT be more accurate than Clock::MS_PER_TICK.
         * In fact, it will always wait slightly more than the parameter, to something rounded up to the nearest multiple of Clock::MS_PER_TICK.
         * @param duration The delay to wait for, in ms
         * @return The actual wait, in ms
         * @see MS_PER_TICK
         */
        static unsigned int delay(unsigned int duration);


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
