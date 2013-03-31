#ifndef ACTIONNERMARTEAU_H_INCLUDED
#define ACTIONNERMARTEAU_H_INCLUDED

#include "lowLevelAction.h"

class ActionnerMarteau : public LowLevelAction {

private:
	int AX12ID;

public:
    ActionnerMarteau(int AX12ID = 0);
    virtual ~ActionnerMarteau();
    /**
     * Update 
     */
	virtual bool update();
};
#endif
