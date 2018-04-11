#ifndef GOLDO2018_H
#define GOLDO2018_H

#define ETAPE_GARAGE 1

#define NOMBRE_ETAPES 30

#include "strategiev3.h"
#include "etape.h"
#include "abeille.h"

class Goldo2018 : public StrategieV3
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    Goldo2018(bool isYellow);

private:

//    /** Nombre d'étapes dans le graph */
//    int nombreEtapes = NOMBRE_ETAPES;

//    /** Numéro de l'étape où le robot va se cacher à la fin */
//    int numeroEtapeGarage = ETAPE_GARAGE;

    /** @brief update du score d'une étape */
    int getScoreEtape(int i);


};


#endif // GOLDO2018_H
