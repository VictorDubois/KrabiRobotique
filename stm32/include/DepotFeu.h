#ifndef DEPOTFEU_H
#define DEPOTFEU_H

#ifdef ROBOTHW
#include "brak.h"
#include "position.h"
#include "strategieV2.h"
#include "odometrie.h"

/// @brief La classe Depot feu permet d aller poser un feu deja pris sur un foyer
class DepotFeu
{
    public:

        DepotFeu(bool isBlue, Position posFoyer, float precision);
        ~DepotFeu();
        int update();

    private:
        bool isBlue;
        float precision;
        Position posFoyer;
        int status;
        Brak* bras;
};

#else
class DepotFeu
{
     public:

        DepotFeu(bool isBlue, Position posFoyer, float precision);
        ~DepotFeu();
        int update();

    private:
        bool isBlue;
        float precision;
        Position posFoyer;
        int status;
        Brak* bras;
};
#endif

#endif // DEPOTFEU_H
