#ifndef INITIALISATION_H
#define INITIALISATION_H

// Initialise le système d'horloge

#include "positionPlusAngle.h"
#include "tirette.h"
#include "quadratureCoderHandler.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "loop.h"
#include "asservissement.h"
#include "interfaceServosNumeriques.h"

class Initialisation
{
    public:
#ifdef ROBOTHW
    Initialisation(PositionPlusAngle start);
#else
    Initialisation(PositionPlusAngle position, bool yellow, Robot* robot = 0);
#endif

        void init();
        bool isYellow();

        Asservissement* getAsservissement();
        Odometrie* getOdometrie();
        StrategieV2* getStrategie();

#ifdef ROBOTHW
        virtual void setYellow() = 0;
#endif
        void setYellow(bool yellow);
        virtual void initClock() = 0;

    // Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
    // On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
        virtual void initGPIO() = 0;

        virtual void initActionneurs() = 0;

    protected:
        PositionPlusAngle start;
        Asservissement* asservissement;
        Odometrie* odometrie;
        StrategieV2* strategie;
        bool yellow;

#ifdef ROBOTHW
        Tirette* tirette;
        QuadratureCoderHandler *rcd, *rcg;
#else
        Robot* robot;
#endif

};
#endif // INITIALISATION_H

