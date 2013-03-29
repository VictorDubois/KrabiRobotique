#include "DiodeMgr.h"

DiodeMgr* DiodeMgr::_singleton = 0;
DiodeMgr::DiodeMgr()
{
    Serial.println("Diode Manager created !");
    led_ctrl1 = new Diode(8);
    led_ctrl2 = new Diode(11);
    led_ctrl3 = new Diode(13);
}

DiodeMgr::~DiodeMgr()
{
    //dtor
}

DiodeMgr* DiodeMgr::singleton()
{
    if (_singleton==0)
        _singleton = new DiodeMgr();
    return _singleton;
}

Diode* DiodeMgr::getLed(int ctrlId)
{
    switch(ctrlId)
    {
        case 1:
            return led_ctrl1;
            break;
        case 2:
            return led_ctrl2;
            break;
        case 3:
            return led_ctrl3;
            break;
    }
    return 0;
}
