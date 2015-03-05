#ifndef BRASLATERAUX_H
#define BRASLATERAUX_H

#ifdef ROBOTHW

#include "servo.h"

#else
#include <stdlib.h>
#endif

/// @brief La classe BrasLateraux permet de controler les bras latéraux destinés à faire tomber les feux.
class BrasLateraux
{
    public:

        BrasLateraux();

        virtual ~BrasLateraux();

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

        /// @brief getBrasLateraux() Renvoit le pointeur de l'objet brasLateraux (pour la stratégie)
        static BrasLateraux* brasLateraux();

    private:

    #ifdef ROBOTHW
        /// @brief brasGauche Servomoteur pouvant faire se déployer ou se replier le bras gauche
        Servo* brasGauche;

        /// @brief brasDroit Servomoteur pouvant faire se déployer ou se replier le bras droit
        Servo* brasDroit;


        /// @brief brasLateraux Adresse de l'objet brasLateraux pour le retrouver dans la stratégie.
        //static BrasLateraux* brasLateraux;
    #endif

};

#endif // BRASLATERAUX_H
