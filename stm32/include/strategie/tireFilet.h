                        #ifndef TIREFILET_H
                                #define TIREFILET_H

#include "mediumLevelAction.h"
#include "math.h"

class TireFilet : public MediumLevelAction
{
    public:
        TireFilet(bool isBlue, Position positionDepart, bool notreCote, float precisionPosition = 30.0f, float precisionAngle = 1.0f);//, Position* positionsTire);
        TireFilet();
        virtual ~TireFilet();
        
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
        Position positionTir;
//        Position positionsTire[6];
//        Position directionsTire[6];
};

#endif // TIRELANCES
