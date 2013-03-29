#ifndef DIODEMGR_H
#define DIODEMGR_H

#include "Diode.h"

class DiodeMgr
{
    public:
        static DiodeMgr* singleton();
        Diode* getLed(int ctrlId);
    protected:
    private:
        DiodeMgr();
        virtual ~DiodeMgr();
        static DiodeMgr* _singleton;

        Diode *led_ctrl1, *led_ctrl2, *led_ctrl3;
};

#endif // DIODEMGR_H
