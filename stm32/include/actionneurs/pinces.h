#ifndef PINCES_H
#define PINCES_H

#define POS_PINCES_OUVERTES 0x01D0
#define POS_PINCES_FERMEES 0x0327
#define POS_PINCES_SAISIR 0x0327
#define INDEX_MOTEUR_PINCE_GAUCHE 10
#define INDEX_MOTEUR_PINCE_DROITE 11

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"
#endif

/** @class Pinces La classe Pinces permet de controler les pinces de Krabi qui servent à attraper les pieds et les gobelets.
*/
class Pinces
{
public:

    static Pinces* getSingleton();

    /// @brief ouvrirPinces() on ouvre la pince
    void ouvrirPinces();

    /// @brief fermerPinces() on ferme la pince
    void fermerPinces();
    void saisirPied();

    bool estDispo();
    void setDispo(bool dispo);


private:


    /** @brief Constructeur
      * @fn Pinces()
    */
    Pinces();

    static Pinces* singleton;

    bool dispo;

    int positionPincesOuvertes;
    int positionPincesFermees;
    int moteurPinceGauche;
    int moteurPinceDroite;
};


#endif // PINCES_H
