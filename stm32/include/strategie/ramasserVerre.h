#ifndef RAMASSERVERRE_H_INCLUDED
#define RAMASSERVERRE_H_INCLUDED

#include "mediumLevelAction.h"

class RamasserVerre : public MediumLevelAction {

public:
    RamasserVerre(int posX = -1, int posY = -1);
    virtual ~RamasserVerre();

	virtual int update();
};
#endif
