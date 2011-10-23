#ifndef PID_FILTER_ANGLE_H_INCLUDED
#define PID_FILTER_ANGLE_H_INCLUDED

#include "variable.h"
#include "Angle.h"

/**@brief Classe permettant de connaitre la vitesse angulaire idéale pour que le robot fasse ce qu'on veut */
class PIDFilterAngle{
    private:
        /**@brief Quantité d'erreurs angulaire ayant eu lieu depuis le début du programme */
        Angle sommeErreurs;
        /**@brief l'erreur ayant eu lieu lors du précédent appelle de getFilteredValue(Angle) */
        Angle erreurPrecedente;
        /**@brief Constancte permettant le calcul correcte de la vitesse angulaire optimal */
        static const float Kp, Ki, Kd;

    public:
        /**@brief constructeur par défault de la classe */
        PIDFilterAngle();
        /**@brief Retourne la vitesse angulaire correcte à appliquer pour corrigé l'erreur d'angle */
        float getFilteredValue(Angle erreur);
};

#endif // PID_FILTER_ANGLE_H_INCLUDED
