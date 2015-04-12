#ifndef BRASTAPIS_H
#define BRASTAPIS_H

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"


/** @class BrasTapis La classe BrasTapis permet de controler les bras sur l'avant de Krabi
*/
class BrasTapis
{
    public:

        enum COTE { DROIT, GAUCHE };

        static BrasTapis* getSingleton(COTE cote);

        /// @brief ouvreBras() ouvre le bras
        void ouvrirBras();

        /// @brief fermeBras() ferme le bras
        void fermerBras();

        /// @brief ouvrirPince() ouvre la pince
        void ouvrirPince();

        /// @brief fermePince() ferme la pince
        void fermerPince();



    private:

        /** @brief Constructeur
          * @fn BrasTapis(char cote)
        */
        BrasTapis(COTE cote);

        static BrasTapis *singleton;

        int positionBrasOuvert;
        int positionBrasFerme;
        int positionPinceOuverte;
        int positionPinceFermee;
        int moteurBras;
        int moteurPinceHaut;
        int moteurPinceBas;

};
#else

class BrasTapis
{
    public:

    enum COTE { DROIT, GAUCHE };

    static BrasTapis* getSingleton(COTE cote);

    /// @brief ouvreBras() ouvre le bras
    void ouvrirBras();

    /// @brief fermeBras() ferme le bras
    void fermerBras();

    /// @brief ouvrirPince() ouvre la pince
    void ouvrirPince();

    /// @brief fermePince() ferme la pince
    void fermerPince();


    private :

        /** @brief Constructeur
          * @fn BrasTapis()
        */
        BrasTapis();

        static BrasTapis *singleton;

        int positionBrasOuvert;
        int positionBrasFerme;
        int positionPinceOuverte;
        int positionPinceFermee;
        int moteurBras;
        int moteurPinceHaut;
        int moteurPinceBas;
};

#endif

#endif // BRASTAPIS_H

