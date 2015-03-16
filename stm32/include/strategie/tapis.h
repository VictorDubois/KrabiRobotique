#ifndef TAPIS_H
#define TAPIS_H

#include "position.h"
#include "mediumLevelAction.h"
#include "command.h"
//#include "brasdevant.h"

/** @class Tapis : le robot doit poser 2 tapis sur les marches.
*/

class Tapis : public MediumLevelAction
{
    public:
        Tapis();
        /** @brief Constructeur
          * @fn Tapis(Position position)
          * @param le paramètre sont de type Position
        */
        Tapis(Position position);
        /** @brief Destructeur
        */
        ~Tapis();
        /** @brief Fonction appelée toutes les 50ms qui gère l'action Tapis : le robot avance à la position puis déploie son bras pour poser le tapis.
          * @fn int update()
          * @return le statut ("status" dans le code) (attribut hérité de la classe MediumLevelAction) :
                status = 0 : le robot commence l'action
                status = 1 : le robot se déplace jusqu'à la position
                status = 2 : le robot s'oriente pour être face aux marches
                status = 3 : le robot ouvre son bras
                status = 54 : le robot lâche le tapis
                status = 105 : le robot ferme son bras
                status = -1 : le robot a fini l'action
        */
        int update();

    protected :
        Position position;
        Position positionMarches;

};


#endif // TAPIS_H
