#ifndef ETEINDREBOUGIE_H_INCLUDED
#define ETEINDREBOUGIE_H_INCLUDED

#include "mediumLevelAction.h"

class EteindreBougie : public MediumLevelAction 
{

private:
	int rotation;
	bool our;
	bool triggered;

public:
    EteindreBougie(int rotation = 0, bool our = false, bool triggered = false);
    virtual ~EteindreBougie();
    
	virtual int update();
};
#endif
