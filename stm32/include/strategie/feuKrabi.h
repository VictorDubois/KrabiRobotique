#ifndef FEUKRABI_H
#define FEUKRABI_H

#include "mediumLevelAction.h"
#include "brak.h"
//#include "strategieV2.h"
#include "odometrie.h"


class FeuKrabi : public MediumLevelAction
{
    public:
        enum ARM_SIDE{LEFT, RIGHT};
        FeuKrabi();
        FeuKrabi(bool isBlue, Position positionDepart, Position positionFeu, float precision = 15.0f);

        int update();

        virtual ~FeuKrabi();
    protected:
    private:
        bool isBlue;
        Position positionDepart;
        float precision;
        Position positionFeu;
        Brak* bracquemart;
        Position positionEtape;

};

#endif // FEUKRABI_H
