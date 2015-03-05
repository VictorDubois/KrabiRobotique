#ifndef CANONFILET_H
#define CANONFILET_H

#ifdef ROBOTHW
//#include "servo.h"
#include "interfaceServosNumeriques.h"

/// @brief La classe CanonFilet permet de controler le canon qui tire un filet sur un mammouth à la fin du match en relachant un ressort armé à la main
class CanonFilet
{
    public:
        static CanonFilet* getSingleton();

        /// @brief shoot() Active le tir du filet en relachant le ressort
        void shoot();
        void attente();

    private:
        static CanonFilet* singleton;
        CanonFilet();

        /// @brief ressort Servomoteur qui permet de relacher le ressort
        //Servo* ressort;
        int MOTEUR;
        int POSITION_ATTENTE;
        int POSITION_TIR;
};

#else
#include <QDebug>
class CanonFilet
{
    public:
        static CanonFilet* getSingleton();

        void shoot();
        void attente();

    private:

        static CanonFilet* singleton;
        CanonFilet();
        int MOTEUR;
        int POSITION_ATTENTE;
        int POSITION_TIR;
};

#endif // ROBOTHW
#endif // CANONFILET_H
