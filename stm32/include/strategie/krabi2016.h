#ifndef KRABI2015_H
#define KRABI2015_H

#define ETAPE_GARAGE 1

#define NOMBRE_ETAPES 50

#include "strategiev3.h"
#include "etape.h"
#include "clap.h"
#include "gobelet.h"
#include "tapis.h"
#include "cabine.h"
#include "ramasserPied.h"
#include "deposerGobelet.h"
#include "manipulationCoinGaucheBas.h"
#include "manipulationCoinGaucheHaut.h"
#include "manipulationCoinGaucheHautPiedSolitaire.h"

class Krabi2016 : public StrategieV3
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    Krabi2016(bool isYellow);

    /** @brief Actions de Krabi */
    Clap actionClap[3];
    Gobelet actionGobelet[5];
    Cabine actionCabine[2];
    DeposerGobelet actionDeposerGobelet[3];
    RamasserPied actionRamasserPied[8];


private:
//    /** Nombre d'étapes dans le graph */
//    int nombreEtapes = NOMBRE_ETAPES;

//    /** Numéro de l'étape où le robot va se cacher à la fin */
//    int numeroEtapeGarage = ETAPE_GARAGE;

    /** @brief update du score d'une étape */
    int getScoreEtape(int i);

};


#endif // Krabi2016_H
