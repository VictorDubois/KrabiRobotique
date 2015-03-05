#ifndef KRABI2015_H
#define KRABI2015_H

#define ETAPE_GARAGE 1
#define NOMBRE_ETAPES 3


#include "strategiev3.h"

#include "feuCote.h"
#include "fresque.h"
#include "feuKrabi.h"
#include "feuCoteKrabi.h"
#include "tireFilet.h"
#include "deposeFruits.h"
#include "tireLances.h"
#include "feukrabilateral.h"
#include "feuCoteKrabi.h"
#include "torchemobile.h"
#include "etape.h"
#include "clap.h"

class Krabi2015 : public StrategieV3
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    Krabi2015(bool isBlue);

    /** @brief Actions de Krabi */
    Clap actionClap[3];


private:
//    /** Nombre d'étapes dans le graph */
//    int nombreEtapes = NOMBRE_ETAPES;

//    /** Numéro de l'étape où le robot va se cacher à la fin */
//    int numeroEtapeGarage = ETAPE_GARAGE;

    /** @brief update du stock et de l'étape */
    void updateStock();

    /** @brief update du score d'une étape */
    int getScoreEtape(int i);

};


#endif // Krabi2015_H
