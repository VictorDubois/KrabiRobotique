#ifndef ROUES_H_INCLUDED
#define ROUES_H_INCLUDED

#include "roue.h"

/**@brief Classe utilisé pour simplifier l'utilisation des roues (puisqu'elles sont forcement deux) */
class Roues{
    public:
        /**@brief Constructeur pour définir les duex roues */
        Roues();
        /**@brief On sauvegarde ces deux roues pour pouvoir les utiliser indépendament */
        Roue gauche,droite;
};

#endif // ROUES_H_INCLUDED
