#ifndef ASCENSEUR_H
#define ASCENSEUR_H

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"
    #include "microSwitch.h"
#endif


/** @class Ascenseur La classe Ascenseur permet de controler les bras sur l'avant de Krabi
*/
class Ascenseur
{

    public:

    static Ascenseur* getSingleton();

        enum STATUS {STOP, UP, DOWN} ;
        void update();

        /// @brief baisserAscenseur() on baisse l'ascenseur
        void baisserAscenseur();

        /// @brief leverAscenseur() on leve l'ascenseur
        void leverAscenseur();

        /// @brief ouvrirAscenseur() on ouvre la pince de l'ascenseur pour attraper un nouveau pied
        void ouvrirAscenseur();

        /// @brief fermerAscenseur() on ferme la pince de l'ascenseur
        void fermerAscenseur();

        /// @brief arreterAscenseur() on stoppe l'ascenseur
        void arreterAscenseur();

        ///// @brief ouvrirPincesAscenseurDepot() on ouvre la pince de l'ascenseur pour lacher les pieds
        //void ouvrirAscenseurDepot();

        bool estEnHaut();
        bool estEnBas();
        bool estOuvert();

        int getNbrPiedsStockes();
        void setNbrPiedsStockes(int NbrPiedsStockes);

        void addPied();
        void resetNbrPiedsStockes();

    private:

        /** @brief Constructeur
          * @fn Ascenseur()
        */
        Ascenseur();

        static Ascenseur *singleton;

        bool ouvert;
        STATUS status;
        int nbrPiedsStockes;
#ifdef ROBOTHW
        MicroSwitch microSwitchBas;
        MicroSwitch microSwitchHaut;
#endif

};


#endif // ASCENSEUR_H



