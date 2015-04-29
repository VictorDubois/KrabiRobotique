#ifndef ASCENSEUR_H
#define ASCENSEUR_H

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"
#endif


/** @class Ascenseur La classe Ascenseur permet de controler les bras sur l'avant de Krabi
*/
class Ascenseur
{

    public:

    static Ascenseur* getSingleton();

        /// @brief baisserAscenseur() on baisse l'ascenseur
        void baisserAscenseur();

        /// @brief leverAscenseur() on leve l'ascenseur
        void leverAscenseur();

        /// @brief ouvrirPincesAscenseurs() on ouvre la pince de l'ascenseur pour attraper un nouveau pied
        void ouvrirPincesAscenseur();

        /// @brief fermerPincesAscenseur() on ferme la pince de l'ascenseur
        void fermerPincesAscenseur();

        /// @brief ouvrirPincesAscenseurDepot() on ouvre la pince de l'ascenseur pour lacher les pieds
        void ouvrirPincesAscenseurDepot();

        int getNbrPiedsStockes();
        void setNbrPiedsStockes(int NbrPiedsStockes);



    private:

        /** @brief Constructeur
          * @fn Ascenseur()
        */
        Ascenseur();

        static Ascenseur *singleton;

        int nbrPiedsStockes;

        int positionAscenseurLeve;
        int positionAscenseurBaisse;
        int positionPincesAscenseurFermees;
        int positionPincesAscenseurOuvertes;
        int positionPincesAscenseurOuvertesDepot;
        int moteurAscenseur;
        int moteurPinceGauche;
        int moteurPinceDroite;

};


#endif // ASCENSEUR_H



