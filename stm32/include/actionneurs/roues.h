#ifndef ROUES_H
#define ROUES_H

#include "roue.h"

/**@brief Classe utilisée pour simplifier l'utilisation des roues (puisqu'elles sont forcement deux) */
class Roues
{
    public:

        /**@brief Constructeur pour définir les deux roues */
        Roues();

        /**@brief On sauvegarde ces deux roues pour pouvoir les utiliser indépendament */
        Roue droite, gauche;
};

#endif // ROUES_H
