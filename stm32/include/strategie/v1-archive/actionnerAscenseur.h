#ifndef ACTIONNERASCENSEUR_H_INCLUDED
#define ACTIONNERASCENSEUR_H_INCLUDED


#include "lowLevelAction.h"
#include "servo.h"

class ActionnerAscenseur : public LowLevelAction {

private:
#ifdef ROBOTHW
	Servo* servos[2];
#endif
    bool close;

public:
    ActionnerAscenseur(bool close = false);
#ifdef ROBOTHW
    ActionnerAscenseur(Servo* servos[2], bool close = false);
#endif
    virtual ~ActionnerAscenseur();

    /**
     * Update continues to trigger the gates (if necessary). It answers true only if the doors have finished moving.
     */
    virtual int update();
};
#endif
