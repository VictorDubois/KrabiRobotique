#ifndef LANCERASCENSEUR_H_INCLUDED
#define LANCERASCENSEUR_H_INCLUDED

#include "lowLevelAction.h"
#include "moteur.h"

class LancerAscenseur : public LowLevelAction {

public:
    LancerAscenseur(int speed = 0, Moteur* motor = 0);
    virtual ~LancerAscenseur();

	/**
	 * says the elevator to go at a certain speed, then answers true. Higher layers will manage the elevator position depending on where it is.
	 */
	virtual bool update();

private:
	int speed;
	Moteur* motor;

};
#endif
