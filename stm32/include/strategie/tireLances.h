#ifndef TIRELANCES_H
#define TIRELANCES_H

#include "constantes.h"
#include "canonLances.h"
#include "mediumLevelAction.h"
#include "math.h"

class TireLances : public MediumLevelAction
{
    public:
    TireLances(bool isBlue, Position positionDepart, bool notreCote, int number, float precisionPosition = 30.0f, float precisionAngle = DEGTORAD(10.f));//, Position* positionsTire);
        TireLances();
        virtual ~TireLances();

        virtual int update();

//        enum BordureFeu
//        {
//            NOTRE_BORDURE = 0,
//            BORDURE_MILIEU = 1,
//            BORDURE_ADVERSAIRE = 2
//        };

        enum CoteDuMammouth
        {
            COTE_DEPART_ADVERSAIRE = 0,
            COTE_NOTRE_DEPART = 1
        };

//        enum SensFeu
//        {
//            NOTRE_COULEUR_VERS_TERRAIN = 0,
//            NOTRE_COULEUR_VERS_EXTERIEUR = 1
//        };
        void lookAt(Angle angle); //Pour orienter le robot

        int getNumber();
        int getNumberDone();

    protected:
    private:
        Position positionDepart;
//        int bordureFeu;
//        bool notreCouleurVersNous;
        bool isBlue;
//        bool sensFeu;
        bool coteDuMammouth;
        float precisionPosition;
        float precisionAngle;
        bool notreCote;
//        Position positionColleBordure;
//        Position positionLookAt;
        Position positionsTire[6];
        Position directionsTire[6];
        Angle lookAtDirection;
        int numberLances, numberDone, timerEnd;
        bool fireLow;
};

#endif // TIRELANCES
