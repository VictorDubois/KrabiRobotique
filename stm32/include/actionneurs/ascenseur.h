#ifndef DEF_ASCENSEUR
#define DEF_ASCENSEUR

#include "limitSwitchSensor.h"
#include "roue.h"

class Ascenseur
{
    public:

        // Constructeur
        Ascenseur(Roue* vis, LimitSwitchSensor* fdcHaut, LimitSwitchSensor* fdcBas);

        // destructeur
        ~Ascenseur();

        // l'ascenseur monte tout en haut
        void monter();

        // l'ascenseur descend tout en bas
        void descendre();

        // met à jour l'état de l'ascenseur pour l'arreter si il est arrivé à son but
        void update();

        // est ce que l'ascenseur a fini sa montée/descente
        bool aFini() const;

        // est ce que l'ascenseur va/est en haut ?
        bool vaEnHaut() const;

        // renvoit l'ascenseur
        static Ascenseur* get();

        // est ce que les fdc sont activés ?
        bool toutEnHaut() const;
        bool toutEnBas() const;

    protected:

        bool m_tourne;
        bool m_vaEnHaut;

        Roue* m_vis;
        LimitSwitchSensor* m_fdcHaut;
        LimitSwitchSensor* m_fdcBas;

        static Ascenseur* m_ascenseur;

};

#endif
