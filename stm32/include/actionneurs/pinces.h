#ifndef PINCES_H
#define PINCES_H

#include "interfaceServosNumeriques.h"

#ifdef ROBOTHW
    #include "servo.h"

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

    bool getEstDispo();
    void setEstDispo();
    void setEstNonDispo();


private:


    /** @brief Constructeur
      * @fn Pinces()
    */
    Pinces();

    static Pinces* singleton;

    bool estDispo;

    int positionPincesOuvertes;
    int positionPincesFermees;
    int moteurPinceGauche;
    int moteurPinceDroite;
};

#else

class Pinces
{
public:

    static Pinces* getSingleton();

    /// @brief ouvrirPinces() on ouvre la pince
    void ouvrirPinces();

    /// @brief fermerPinces() on ferme la pince
    void fermerPinces();

    bool getEstDispo();
    void setEstDispo();
    void setEstNonDispo();


private:


    /** @brief Constructeur
      * @fn Pinces()
    */
    Pinces();

    static Pinces* singleton;

    bool estDispo;

    int positionPincesOuvertes;
    int positionPincesFermees;
    int moteurPinceGauche;
    int moteurPinceDroite;
};

#endif

#endif // PINCES_H
