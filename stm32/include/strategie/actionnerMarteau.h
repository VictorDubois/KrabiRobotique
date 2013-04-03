#ifndef ACTIONNERMARTEAU_H_INCLUDED
#define ACTIONNERMARTEAU_H_INCLUDED


#include "lowLevelAction.h"

class ActionnerMarteau : public LowLevelAction {

private:
	int AX12ID;
	int goalAngle;
	int speed;

public:
    ActionnerMarteau(int AX12ID = 0, int goalAngle = 0x00, int speed = 0x00);
    virtual ~ActionnerMarteau();
    /**
     * Update
     */
    virtual int update();
};
#endif
