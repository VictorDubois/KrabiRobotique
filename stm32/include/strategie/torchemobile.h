#ifndef TORCHEMOBILE_H
#define TORCHEMOBILE_H

#include "mediumLevelAction.h"
#include "brak.h"
//#include "strategieV2.h"


class TorcheMobile : public MediumLevelAction
{
    public:
        TorcheMobile();
        TorcheMobile(bool isBlue, Position positionDepart, Position positionTorche, bool opponentSide = false, float precision = 10.0f);
        int update();
    protected:
    private:
        bool isBlue;
        Position positionDepart;
        Position positionTorche;
        float precision;
        bool opponentSide;
        void deposeFeu(int numero);
        void prendFeu(int numero);
        Angle angle;

        Brak* bracquemart;


};

#endif // TORCHEMOBILE_H
