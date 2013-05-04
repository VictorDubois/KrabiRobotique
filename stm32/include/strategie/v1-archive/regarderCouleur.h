#ifndef REGARDERCOULEUR_H_INCLUDED
#define REGARDERCOULEUR_H_INCLUDED

#include "lowLevelAction.h"
#include "sensors.h"

class RegarderCouleur : public LowLevelAction {


public:
    RegarderCouleur(Sensors* sensors = NULL);
    virtual ~RegarderCouleur();

    /**
     * Update answers true if the color has been checked. update returns .
     */
    virtual int update();

private:
	Sensors* sensors;
};
#endif
