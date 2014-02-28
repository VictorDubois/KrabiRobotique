#ifndef STRATEGIEV3_H
#define STRATEGIEV3_H
#include "actionGoTo.h"
#include "mediumLevelAction.h"
#include "dijkstra.h"
#define NOMBRE_ETAPES 10

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
private:
    /** @brief tableau des actions qu'on peut décider de faire. TODO : mettre à jour ce tableau, en incluant des actions plus diverses */
    ActionGoTo actionEtape[10];

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
};

#endif // STRATEGIEV3_H
