#ifndef ETEINDREBOUGIE_H_INCLUDED
#define ETEINDREBOUGIE_H_INCLUDED

#include "mediumLevelAction.h"

class EteindreBougie : public MediumLevelAction
{
public:
    EteindreBougie(Position position = Position(-1,-1), int rotation = 0, int our = 0, bool triggered = false, bool high = false);
    virtual ~EteindreBougie();

    virtual int update();

private:
	int rotation;
    int color; // 0= not checked; 1=blue; 2=red; 3=white
	bool triggered;
    bool high;

};
#endif
