#ifndef FeuKrabiLateral_H
#define FeuKrabiLateral_H

#include "mediumLevelAction.h"
#include "brak.h"
//#include "strategieV2.h"
#include "odometrie.h"
#include "braslateral.h"


class FeuKrabiLateral : public MediumLevelAction
{
    public:
        enum ARM_SIDE{LEFT, RIGHT};
        FeuKrabiLateral();
        FeuKrabiLateral(bool isBlue, Position positionDepart, Angle angleBefore, ARM_SIDE arm, float precision = 15.0f);

        int update();

        virtual ~FeuKrabiLateral();
    protected:
    private:
        bool isBlue;
        Position positionDepart;
        float precision;
        Position positionFeu;
        Brak* bracquemart;
        Position positionEtape;
        Angle angleBefore, angleAfter;
        ARM_SIDE arm;

};

#endif // FeuKrabiLateral_H
