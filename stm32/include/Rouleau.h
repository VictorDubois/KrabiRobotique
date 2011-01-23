#ifndef ROULEAU_H_INCLUDED
#define ROULEAU_H_INCLUDED

#include "Moteur.h"

class Rouleau : public Moteur {
    private:
        float dutyCycle;
    public:
        Rouleau(float dutyCycle);
        void avaleBoule();
        void recracheBoule();
        void arrete();
};
#endif // ROULEAU_H_INCLUDED
