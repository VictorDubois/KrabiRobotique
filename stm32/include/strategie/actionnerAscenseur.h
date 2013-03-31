#ifndef ACTIONNERASCENSEUR_H_INCLUDED
#define ACTIONNERASCENSEUR_H_INCLUDED

#include "lowLevelAction.h"

class ActionnerAscenseur : public LowLevelAction {

private:
	Servo* servos[2];
	bool fermer;

public:
    ActionnerAscenseur(Servo* servos[2] = {NULL,NULL});
    virtual ~ActionnerAscenseur();

    /**
     * Update continues to trigger the gates (if necessary). It answers true only if the doors have finished moving.
     */
	virtual bool update();
};
#endif
