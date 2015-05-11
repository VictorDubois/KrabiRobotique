#ifndef TAPIS_H
#define TAPIS_H

#include "position.h"
#include "angle.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "brasTapis.h"

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

        */
        int update();

        Etape::EtapeType getType();

    protected :
        Position position;
        Angle toLookAt;
        BrasTapis::COTE cote;
};


#endif // TAPIS_H
