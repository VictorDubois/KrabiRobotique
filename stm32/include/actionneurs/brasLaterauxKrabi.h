#ifndef BRASLATERAUX_H
#define BRASLATERAUX_H

#ifdef ROBOTHW

#include "servo.h"

#else
#include <stdlib.h>
#endif

/// @brief La classe BrasLaterauxKrabi permet de controler les bras latéraux de Krabi
class BrasLaterauxKrabi
{
    public:

        BrasLaterauxKrabi();

        virtual ~BrasLaterauxKrabi();

        bool brasGaucheDeploye;
        bool brasDroitDeploye;

        /// @brief deployerBrasGauche() Déploie le bras gauche à 90°
        void deployerBrasGauche();

        /// @brief replierBrasGauche() Replie le bras gauche
        void replierBrasGauche();


        /// @brief deployerBrasDroit() Déploie le bras droit à 90°
        void deployerBrasDroit();

        /// @brief replierBrasDroit() Replie le bras droit à 90°
        void replierBrasDroit();

        /// @brief getBrasLaterauxKrabi() Renvoit le pointeur de l'objet brasLaterauxKrabi (pour la stratégie)
        static BrasLaterauxKrabi* brasLaterauxKrabi();

    private:

    #ifdef ROBOTHW
        /// @brief brasGauche Servomoteur pouvant faire se déployer ou se replier le bras gauche
        Servo* brasGauche;

        /// @brief brasDroit Servomoteur pouvant faire se déployer ou se replier le bras droit
        Servo* brasDroit;


        /// @brief brasLaterauxKrabi Adresse de l'objet brasLaterauxKrabi pour le retrouver dans la stratégie.
        static BrasLaterauxKrabi* brasLaterauxKrabi;
    #endif

};

#endif // BRASLATERAUX_H
