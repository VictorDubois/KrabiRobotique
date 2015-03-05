#ifndef STRATEGIEV3_H
#define STRATEGIEV3_H
#include "actionGoTo.h"
#include "mediumLevelAction.h"
#include "dijkstra.h"
#include "feuCote.h"
#include "fresque.h"
#include "strategieV2.h"
#ifndef ROBOTHW
#include <QPainter>
#endif

#ifdef KRABI
    #define NOMBRE_ETAPES 22//22//10
#endif
#ifdef KRABI_JR
    #define NOMBRE_ETAPES 31//22//10
#endif
//#define NOMBRE_ETAPES 10
class StrategieV3 : public MediumLevelAction
{
public:
    /** @brief Constructeur de la stratégie *
    * @param isBlue le côté de départ */
    StrategieV3(bool isBlue);

    /** @brief Update la stratégie, soit parceque le robot est arrivé à une étape, soit parcequ'il vient d'éviter un autre robot *
    * @return Le status  : 1 = vers une étape-objectif, 2 = vers une étape intermédiaire, -1 = stratégie finie, plus rien à faire */
    virtual int update();

    /** @brief COnfigure la stratégie pour prendre en compte le fait qu'on vient de voir un robot */
    virtual void collisionAvoided();

    /** @brief Met à jour la trajectoire pour se diriger vers une étape intermédiaire */
    void updateIntermedaire();

    void resetEverything();

#ifndef ROBOTHW
    virtual void paint(QPainter* p);
#endif

private:
    /** @brief tableau des actions qu'on peut décider de faire. TODO : mettre à jour ce tableau, en incluant des actions plus diverses */
    MediumLevelAction* actionEtape[NOMBRE_ETAPES];

    ActionGoTo actionGoto[NOMBRE_ETAPES];

#ifdef KRABI
    Fresque actionFresque[3];
#endif
#ifdef KRABI_JR
    FeuCote actionFeuCote[6];
#endif

    /** @brief la classe dijkstra pour calculer les distances */
    Dijkstra* dijkstra;

    /** @brief le tableau des étapes constituant le graphe à explorer */
    Etape** tableauEtapes;

    /** @brief le numéro de l'étape en cours */
    int etapeEnCours;

    /** @brief vient-on de détecter un robot */
    bool avoiding;

    /** @brief le numéro de l'étape-objectif */
    int goal;

    /** @brief le status de la stratégie : 1 = vers une étape-objectif, 2 = vers une étape intermédiaire, -1 = stratégie finie, plus rien à faire */
    int statusStrat;

    /** @brief status du robot, est-il en train d'éviter en reculant */
    bool enTrainEviterReculant;

    /** @brief status du robot, est-il en train d'éviter en avancant */
    bool enTrainEviterAvancant;

    /** @brief nombre de fruits transporte par le robot */
    int nombreFruitsTransporte;

    /** @brief nombre de feux transporte par le robot */
    int nombreFeuxTransporte;

    /** @brief nombre de fresques transporte par le robot */
    int nombreFresquesTransporte;

    /** @brief nombre de lances transporte par le robot */
    int nombreLancesTransporte;
};

#endif // STRATEGIEV3_H
