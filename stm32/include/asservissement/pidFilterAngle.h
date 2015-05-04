#ifndef PIDFILTERANGLE_H
#define PIDFILTERANGLE_H

#include "constantes.h"
#include "angle.h"

/**@brief Classe permettant de connaitre la vitesse angulaire idéale pour que le robot fasse ce qu'on veut */
class PIDFilterAngle
{
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

        /**@brief Retourne la vitesse angulaire correcte à appliquer pour corriger l'erreur d'angle */
        float getFilteredValue(Angle erreur);

        /**@brief Reset les erreurs, pour repartir doucement après un arrêt*/
        void resetErrors();
};

#endif // PID_FILTER_ANGLE_H
