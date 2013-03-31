#ifndef REGARDERCOULEUR_H_INCLUDED
#define REGARDERCOULEUR_H_INCLUDED

class RegarderCouleur : LowLevelAction {


public:
    LowLevelAction(Sensors* sensors = NULL);
    virtual ~LowLevelAction();

    /**
     * Update answers true if the color has been checked. It has to store the color somewhere (isBlue) to answer after (getBlue()).
     */
	virtual bool update();

private:
	Sensors* sensors;
};
#endif
