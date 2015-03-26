#ifndef CLAP_H
#define CLAP_H

#include "mediumLevelAction.h"
#include "actionGoTo.h"

class Clap : public MediumLevelAction
{
    public:
        Clap();
        Clap(bool isGreen, Position positionDepart, Position positionFin);
        int update();

    private :
        bool isGreen;
        Position positionDepart;
        Position positionFin;
        Position versLaGauche;
        Position versLaDroite;
        Position direction;
        ActionGoTo deplacement;

};

#endif // CLAP_H
