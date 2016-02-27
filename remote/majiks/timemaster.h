#ifndef TIMEMASTER_H
#define TIMEMASTER_H

#include <QTime>

class TimeMaster
{
    public:
        static TimeMaster* getInstance();

        void reset();
        int getCurrentTime() const;

        void delta(int delta);

    private:
        explicit TimeMaster();

        QTime m_syncTime;
        int m_timerAdjust;
};

#endif // TIMEMASTER_H
