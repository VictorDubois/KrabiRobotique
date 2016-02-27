#include "timemaster.h"

TimeMaster* TimeMaster::getInstance()
{
    static TimeMaster* instance = nullptr;
    if(!instance)
        instance = new TimeMaster();
    return instance;
}

TimeMaster::TimeMaster()
{
    reset();
}

void TimeMaster::delta(int delta)
{
    m_timerAdjust = delta - m_syncTime.elapsed();
}

void TimeMaster::reset()
{
    m_syncTime.restart();
    m_timerAdjust = -m_syncTime.elapsed();
}

int TimeMaster::getCurrentTime() const
{
    return m_syncTime.elapsed() + m_timerAdjust;
}


