#ifndef VALEURSROUES_H_INCLUDED
#define VALEURSROUES_H_INCLUDED

#include <stdint.h>

/**@brief Permet de stocker des valeurs pour chaque roue */
class ValeursRoues{
    private:
    /**@brief Permet de stocker la valeur pour la roue gauche */
    uint32_t gauche;
    /**@brief Permet de stocker la valeur pour la roue droite */
    uint32_t droite;

    public:
    /**@brief Constructeur prennant les parametre initial pour chaque roue */
    ValeursRoues(uint32_t gauche_d, uint32_t droite_d);
    /**@brief Constructeur par default */
    ValeursRoues();
    /**@brief Retourne la valeur de la roue gauche */
    uint32_t getRoueGauche();
    /**@brief Retourne la valeur pour la roue droite */
    uint32_t getRoueDroite();
    /**@brief change la valeur de la roue gauche */
    void setRoueGauche(uint32_t gauche_d);
    /**@brief Change la valeur pour la roue droite */
    void setRoueDroite(uint32_t droite_d);
};

#endif // VALEURSROUES_H_INCLUDED
