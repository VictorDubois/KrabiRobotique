#ifndef PIDFILTERDISTANCE_H
#define PIDFILTERDISTANCE_H

#include "constantes.h"
#include "distance.h"

/**@brief Classe permettant de connaitre la vitesse linéaire idéale pour que le robot fasse ce qu'on veut */
class PIDFilterDistance
{
    private:

        /**@brief Quantité d'erreurs linéaire ayant eu lieu depuis le début du programme */
        Distance sommeErreurs;

        /**@brief l'erreur ayant eu lieu lors du précédent appel de getFilteredValue(Distance) */
        Distance erreurPrecedente;

        /**@brief Constantes permettant le calcul correct de la vitesse linéaire optimale */
        static const float Kp, Ki, Kd;

    public:

        /**@brief constructeur par défault de la classe */
        PIDFilterDistance();

        /**@brief Retourne la vitesse linéaire correcte à appliquer pour corrigé l'erreur de distance */
        float getFilteredValue(Distance erreur);
};

#endif // PIDFILTERDISTANCE_H
