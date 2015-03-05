#ifndef FEUCOTE_H
#define FEUCOTE_H

#include "mediumLevelAction.h"
#include "braslateral.h"

class FeuCote : public MediumLevelAction
{
    public:
        FeuCote(bool isBlue, Position positionDepart, int bordureFeu, bool sensFeu, bool coteDuFeu, float precision = 30.0f);
        FeuCote();
        virtual ~FeuCote();

        virtual int update();

        enum BordureFeu
        {
            NOTRE_BORDURE = 0,
            BORDURE_MILIEU = 1,
            BORDURE_ADVERSAIRE = 2
        };

        enum CoteDuFeu
        {
            COTE_DEPART_ADVERSAIRE = 0,
            COTE_NOTRE_DEPART = 1
        };

        enum SensFeu
        {
            NOTRE_COULEUR_VERS_TERRAIN = 0,
            NOTRE_COULEUR_VERS_EXTERIEUR = 1
        };

    protected:
    private:
        Position positionDepart;
        int bordureFeu;
        bool notreCouleurVersNous;
        bool isBlue;
        bool sensFeu;
        bool coteDuFeu;
        float precision;
        Position positionColleBordure;
        Position positionLookAt;
};

#endif // FEUCOTE_H
