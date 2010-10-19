#ifndef VALEURSCAPTEURS_H_INCLUDED
#define VALEURSCAPTEURS_H_INCLUDED

#include <stdint.h>

class ValeursCapteurs
{
        public:
            uint16_t devant;
            uint16_t derrière;
            uint16_t gauche;
            uint16_t droite;
            uint16_t seuil;
        private:
           // les capteurs en private ? des getters ça paraît chiant...


};

#endif // VALEURSCAPTEURS_H_INCLUDED
