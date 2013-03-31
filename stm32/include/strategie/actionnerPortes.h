#ifndef ACTIONNERPORTES_H_INCLUDED
#define ACTIONNERPORTES_H_INCLUDED

#include "lowLevelAction.h"
#include "servo.h"

class ActionnerPortes : public LowLevelAction {

private:
	Servo* servos[2];
	bool close;

public:
    ActionnerPortes(bool close = false);
    ActionnerPortes(Servo* servos[2], bool close = false);
    virtual ~ActionnerPortes();
    /**
     * Update continues to trigger the gates (if necessary). It answers true only if the doors have finished moving.
     */
	virtual bool update();
};
#endif
