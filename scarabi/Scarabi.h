#ifndef SCARABI_H
#define SCARABI_H

#include "Move.h"
#include "DiodeMgr.h"
#include <Arduino.h>

#define PIN_COLOR   6
#define PIN_TIRETTE A2
#define TIME_MATCH  90000000
#define TIME_INFO   5000000

class Scarabi
{
    public:
        static Scarabi* singleton();
        enum sideColor{colorRed, colorBlue};
        void waitTirette(bool avoid = false);
        void update();
        void finalStop();
        sideColor getColor();

    protected:
    private:
        static Scarabi* _singleton;
        Scarabi();
        virtual ~Scarabi();

        bool isRunning;
        long matchTimeInfo, timerMatchStarted, currentTimer, previousTimer;
        sideColor color;
};

#endif // SCARABI_H
