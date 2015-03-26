#ifndef KRABI2014_H
#define KRABI2014_H

#define NOMBRE_ETAPES 31
#define ETAPE_GARAGE 25

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

class Krabi2014 : public StrategieV3
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    Krabi2014(bool isBlue);

    /** @brief Actions de Krabi */
    Fresque actionFresque[3];
    FeuKrabi actionFeuKrabi[2];
    TireFilet actionFiletKrabi[2];
    TireLances actionLancesKrabi[2];
    FeuCoteKrabi actionFeuCoteKrabi[4];
    FeuKrabiLateral actionFeuKrabiLateral[4];
    TorcheMobile actionTorcheMobile[2];

private:
    /** @brief nombre de fruits transporte par le robot */
    int nombreFruitsTransporte;

    /** @brief nombre de feux transporte par le robot */
    int nombreFeuxTransporte;

    /** @brief nombre de fresques transporte par le robot */
    int nombreFresquesTransporte;

    /** @brief nombre de lances transporte par le robot */
    int nombreLancesTransporte;

    /** @brief nombre de filets transporte par le robot */
    int nombreFiletTransporte;

    /** @brief update du stock et de l'étape */
    void updateStock();

    /** @brief update du score d'une étape */
    int getScoreEtape(int i);

};


#endif // KRABI2014_H
