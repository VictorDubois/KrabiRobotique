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

        /// @brief ouvreBras() ouvre le bras
        void baisserAscenseur();

        /// @brief fermeBras() ferme le bras
        void leverAscenseur();

        /// @brief ouvrirPince() ouvre la pince
        void ouvrirPincesAscenseurs();

        /// @brief fermePince() ferme la pince
        void fermerPincesAscenseur();



    private:

        /** @brief Constructeur
          * @fn BrasTapis(char cote)
        */
        Ascenseur();

        static Ascenseur *singleton;

        int positionAscenseurLeve;
        int positionAscenseurBaisse;
        int positionPincesAscenseurOuvertes;
        int positionPincesAscenseurFermees;
        int moteurAscenseur;
        int moteurPinceGauche;
        int moteurPinceDroite;

};

#else

class Ascenseur
{
    public:

    static Ascenseur* getSingleton();

    /// @brief ouvreBras() ouvre le bras
    void baisserAscenseur();

    /// @brief fermeBras() ferme le bras
    void leverAscenseur();

    /// @brief ouvrirPince() ouvre la pince
    void ouvrirPincesAscenseurs();

    /// @brief fermePince() ferme la pince
    void fermerPincesAscenseur();


    private :

        /** @brief Constructeur
          * @fn Ascenseur()
        */
        Ascenseur();

        static Ascenseur *singleton;

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



