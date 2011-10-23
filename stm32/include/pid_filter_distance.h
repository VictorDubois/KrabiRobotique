#ifndef PID_FILTER_DISTANCE_H_INCLUDED
#define PID_FILTER_DISTANCE_H_INCLUDED

#include "variable.h"
#include "distance.h"

/**@brief Classe permettant de connaitre la vitesse linéaire idéale pour que le robot fasse ce qu'on veut */
class PIDFilterDistance{
    private:
        /**@brief Quantité d'erreurs linéaire ayant eu lieu depuis le début du programme */
        Distance sommeErreurs;
        /**@brief l'erreur ayant eu lieu lors du précédent appelle de getFilteredValue(Distance) */
        Distance erreurPrecedente;
        /**@brief Constancte permettant le calcul correcte de la vitesse linéaire optimal */
        static const float Kp, Ki, Kd;

    public:
        /**@brief constructeur par défault de la classe */
        PIDFilterDistance();
        /**@brief Retourne la vitesse linéaire correcte à appliquer pour corrigé l'erreur de distance */
        float getFilteredValue(Distance erreur);
};

#endif // PID_FILTER_DISTANCE_H_INCLUDED
