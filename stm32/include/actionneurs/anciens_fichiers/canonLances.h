#ifndef CANONLANCES_H
#define CANONLANCES_H

#ifdef ROBOTHW
#include "servo.h"
#include "moteur.h"

/// @brief La classe CanonLances permet de controler le canon à lances (balles de ping-pong à tirer sur les mammouths)
class CanonLances
{
    public:
        static CanonLances* getSingleton();

        /// @brief shootAtWill() Active le tir des balles
        void shootAtWill();

        /// @brief shootAtWillLow() Règle la vitesse pour tirer plus bas
        void shootAtWillLow();

        /// @brief stopShootAtWill() Arrête le tir des lances
        void stopShootAtWill();

        /// @brief arm() Arme le canon d'une balle
        void arm();

        /// @brief fire() Tire la balle en la plaçant dans le canon
        void fire();

    private:
        static CanonLances* singleton;
        CanonLances();

        /// @brief moteurTir Moteur qui fait tourner la roue pour accélérer les balles et les propulser
        Moteur* moteurTir;

        /// @brief servoCharge Servomoteur qui charge le canon
        Servo* servoCharge;
};

#else
class CanonLances
{
    public:
        static CanonLances* getSingleton();

        void shootAtWill();
        void shootAtWillLow();
        void stopShootAtWill();
        void arm();
        void fire();

    private:
        static CanonLances* singleton;
        CanonLances();
};
#endif

#endif // CANONLANCES_H
