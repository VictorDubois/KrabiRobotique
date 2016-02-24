#ifndef KrabiJunior2016_H
#define KrabiJunior2016_H

#define ETAPE_GARAGE 1
#define NOMBRE_ETAPES 10


#include "strategiev3.h"
#include "etape.h"
#include "clap.h"

class KrabiJunior2016 : public StrategieV3
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    KrabiJunior2016(bool isYellow);

    /** @brief Actions de KrabiJunior */


private:
//    /** Nombre d'étapes dans le graph */
//    int nombreEtapes = NOMBRE_ETAPES;

//    /** Numéro de l'étape où le robot va se cacher à la fin */
//    int numeroEtapeGarage = ETAPE_GARAGE;

    /** @brief update du score d'une étape */
    int getScoreEtape(int i);

};



#endif // KrabiJunior2016_H
