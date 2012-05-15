#ifndef BRAS_H
#define BRAS_H

#ifdef ROBOTHW

#include "Servo.h"

/** @brief La classe Bras permet de contrôler les différents organes du robot actionnés par des servomoteurs
**/

class Bras
{
    public:
        Bras();
        virtual ~Bras();

        /// @brief bras Adresse de l'objet bras pour le retrouver dans la stratégie.
        static Bras* bras;

        /// @brief ouvrirBalaiDroit() Ouvre le balai droit (et ferme le gauche).
        void ouvrirBalaiDroit();
        /// @brief ouvrirBalaiGauche() Ouvre le balai gauche (et ferme le droit).
        void ouvrirBalaiGauche();
        /// @brief ouvrirBalaiDroit() Ferme le balai droit.
        void fermerBalaiDroit();
        /// @brief ouvrirBalaiGauche() Ferme le balai gauche.
        void fermerBalaiGauche();
        /// @brief fermerBalais() Ferme les deux balais.
        void fermerBalais();
        /// @brief ouvrirBalais() Ouvrir les deux balais.
        void ouvrirBalais();
        /// @brief monterRateau() Fait tourner le rateau jusqu'a sa position haute.
        void monterRateau();
        /// @brief descendreRateau() Fait descendre le rateau jusqu'a sa position haute.
        void descendreRateau();
        /// @brief dropRateau() Désactive le servo pour faire tomber le rateau
        void dropRateau();
        /// @brief arretUrgence() Coupe tous les servo utilisés.
        void arretUrgence();
        /// @brief getBras() Renvoit le pointeur de l'objet bras (pour la stratégie)
        Bras* getBras();


    protected:
    private:
        /// @brief balaiGauche Servomoteur controlant le balai de gauche.
        Servo* balaiGauche;
        /// @brief balaiDroite Servomoteur controlant le balai de droite.
        Servo* balaiDroite;
        /// @brief rateau Servomoteur controlant le rateau.
        Servo* rateau;

};

#endif // BALAI_H
#endif // ROBOTHW
