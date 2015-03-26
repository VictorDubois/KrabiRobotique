#ifndef FEUCOTEKRABI_H
#define FEUCOTEKRABI_H

#include "mediumLevelAction.h"
#include "brak.h"


class FeuCoteKrabi : public MediumLevelAction
{
    public:
        FeuCoteKrabi();
        FeuCoteKrabi(bool isBlue, Position positionDepart, int type, float precision = 30);
        int update();
    protected:
    private:
        bool isBlue;
        Position positionDepart;
        float precision;
        int type;
        Brak* bracquemart;
        Position positionChopperFeu;

};

#endif // FEUCOTEKRABI_H
