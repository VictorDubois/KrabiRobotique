#ifndef RECALIBRERODOMETRIE_H_INCLUDED
#define RECALIBRERODOMETRIE_H_INCLUDED

#include "mediumLevelAction.h"
#include "limitSwitchSensor.h"

class RecalibrerOdometrie : public MediumLevelAction
{
    public:
        RecalibrerOdometrie(bool isBlue, Position positionDepart, int coinRecalage);
        RecalibrerOdometrie();
        virtual ~RecalibrerOdometrie();

        virtual int update();

        enum CoinRecalage
        {
            COTE_DEPART_ADVERSAIRE_HAUT = 0,
            COTE_DEPART_ADVERSAIRE_BAS = 1,
            COTE_NOTRE_DEPART_HAUT = 2,
            COTE_NOTRE_DEPART_BAS = 3
        };

    protected:
    private:
        Position positionDepart;
//        Position goalPosition1;
//        Position goalPosition2;
        Position candidatPositionArrete;
        int coinRecalage;
        bool isBlue;
};

#endif // RECALIBRERODOMETRIE_H_INCLUDED
