#ifndef CLAP_H
#define CLAP_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "braslateral.h"

/** @class clap : le robot doit fermer 3 claps du bord de la table
*/

class Clap : public MediumLevelAction
{
    public:
        Clap();
        /** @brief Constructeur
          * @fn Clap(Position positionDepart, Position positionArrivee)
          * @param les paramètres sont de type Position
        */
        Clap(Position positionDepart, Position positionArrivee);
        /** @brief Destructeur
        */
        ~Clap();
        /** @brief Fonction appelée toutes les 50ms qui gère l'action Clap : le robot avance à la position de départ, ouvre son bras, avance à la position d'arrivée, ferme son bras.
          * @fn int update()
          * @return le statut ("status" dans le code) (attribut hérité de la classe MediumLevelAction) :
                status = 0 : le robot commence l'action
                status = 1 : le robot se déplace jusqu'à la position de départ
                status = 2 : le robot s'oriente pour présenter son coté au clap
                status = 3 : le robot ouvre son bras
                status = 54 : le robot avance à la position d'arrivée
                status = 55 : le robot ferme son bras
                status = -1 : le robot a finit l'action
        */
        int update();

    protected :
        Position positionDepart;
        Position positionArrivee;

};

#endif // CLAP_H
