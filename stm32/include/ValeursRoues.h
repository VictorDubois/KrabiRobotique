#ifndef VALEURSROUES_H_INCLUDED
#define VALEURSROUES_H_INCLUDED

#include <stdint.h>

class ValeursRoues{
    private:
    uint32_t gauche;
    uint32_t droite;

    public:
    ValeursRoues(uint32_t gauche_d, uint32_t droite_d);
    ValeursRoues();
    uint32_t getRoueGauche();
    uint32_t getRoueDroite();
    void setRoueGauche(uint32_t gauche_d);
    void setRoueDroite(uint32_t droite_d);
};

#endif // VALEURSROUES_H_INCLUDED
