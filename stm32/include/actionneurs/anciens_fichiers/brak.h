#ifndef BRAK_H
#define BRAK_H

#include "interfaceServosNumeriques.h"

/// @brief La classe Brak permet de contrôler le bracquemart de Krabi
class Brak
{
public:

    static Brak* getSingleton();


    /// @brief abaisse le bracquemart de Krabi
    void positionBasse();

    /// @brief positionne le bracquemart de Krabi à une position entre la position haute et la position basse
    void positionIntermediaire();

    /// @brief remonte le braquemart de Krabi
    void positionHaute();

    /// @brief positionne pour mettre à la hauteur du feu du haut d'une torche mobile
    void positionFeuHautTorche();

    /// @brief positionne pour mettre à la hauteur du feu du milieu d'une torche mobile
    void positionFeuMilieuTorche();

    /// @brief positionne pour mettre à la hauteur du feu du bas d'une torche mobile
    void positionFeuBasTorche();

    /// @brief attrape un feu placé sous le bras de Krabi
    void attraperFeu();

    /// @brief relache le feu que tenait Krabi
    void relacherFeu();

    ///@brief place le bracquemart au bon endroit pour relacher le feu quand retourné
    void positionBasseRetourne();

    /// @brief oriente vers le haut
    void orienterHaut();

    /// @brief oriente vers le bas
    void orienterBas();

private:

    static Brak* singleton;
    Brak();

    // les différentes positions du moteur du haut
    int POSITION_RANGE;
    int POSITION_INTERMEDIAIRE;
    int POSITION_FEU_HAUT_TORCHE;
    int POSITION_FEU_MILIEU_TORCHE;
    int POSITION_FEU_BAS_TORCHE;
    int POSITION_FEU_TABLE;
    int POSITION_RETOURNEE;

    // les deux positions du moteur du bas
    int VENTOUSE_VERS_BAS;
    int VENTOUSE_VERS_HAUT;

    // id des moteurs
    int MOTEUR_BAS;
    int MOTEUR_HAUT;

};

#endif // BRAK_H
