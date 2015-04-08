#ifndef ASCENSEUR_H
#define ASCENSEUR_H

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"


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

        /// @brief ouvrirPincesAscenseurs() on ouvre la pince de l'ascenseur
        void ouvrirPincesAscenseur();

        /// @brief fermerPincesAscenseur() on ferme la pince de l'ascenseur
        void fermerPincesAscenseur();

        int getNbrPiedsStockes();
        int setNbrPiedsStockes(int NbrPiedsStockes);

        int positionAscenseurLeve;
        int positionAscenseurBaisse;
        int positionPincesAscenseurOuvertes;
        int positionPincesAscenseurFermees;
        int moteurAscenseur;
        int moteurPinceGauche;
        int moteurPinceDroite;


    private:

        /** @brief Constructeur
          * @fn BrasTapis()
        */
        Ascenseur();

        static Ascenseur *singleton;

        int nbrPiedsStockes;

};

#else

class Ascenseur
{
    public:

    static Ascenseur* getSingleton();

    /// @brief baisserAscenseur() on baisse l'ascenseur
    void baisserAscenseur();

    /// @brief leverAscenseur() on leve l'ascenseur
    void leverAscenseur();

    /// @brief ouvrirPincesAscenseurs() on ouvre la pince de l'ascenseur
    void ouvrirPincesAscenseur();

    /// @brief fermerPincesAscenseur() on ferme la pince de l'ascenseur
    void fermerPincesAscenseur();

    int getNbrPiedsStockes();
    int setNbrPiedsStockes(int NbrPiedsStockes);


    private :

        /** @brief Constructeur
          * @fn Ascenseur()
        */
        Ascenseur();

        static Ascenseur *singleton;

        int nbrPiedsStockes;

        int positionAscenseurLeve;
        int positionAscenseurBaisse;
        int positionPincesAscenseurOuvertes;
        int positionPincesAscenseurFermees;
        int moteurAscenseur;
        int moteurPinceGauche;
        int moteurPinceDroite;

};

#endif

#endif // ASCENSEUR_H



