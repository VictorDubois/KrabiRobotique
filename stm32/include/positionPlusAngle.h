#ifndef POSITIONPLUSANGLE_H
#define POSITIONPLUSANGLE_H

#include "position.h"
#include "angle.h"

/// @brief Classe permettant d'avoir la position du robot par rapport à l'angle de la table et son angle par rapport à l'absisse.
class PositionPlusAngle
{
    public:
        /**@brief Constructeur de la classe.
         *@param Position pos est la position du robot au moment ou l'on déclare la classe
         *@param Angle ang est l'angle du robot au moment ou l'on déclare la classe.*/
        PositionPlusAngle(const Position& pos, Angle ang);

        /// @brief Constructeur par défault de la classe.
        PositionPlusAngle();

        /// @brief Constructeur de copie.
        PositionPlusAngle(const PositionPlusAngle& original);

        /// @brief Surcharge d'opérateur pour ajouter une distance.
        PositionPlusAngle operator+(Distance distance) const;

        /// @brief Surcharge d'opérateur pour ajouter deux PositionPlusAngle (chaque paramètre deux à deux).
        PositionPlusAngle operator+(const PositionPlusAngle& posAngAdd) const;

        /// @brief Surcharge d'opérateur pour enlever une distance.
        PositionPlusAngle operator-(Distance distance) const;

        /// @brief Surcharge d'opérateur pour assigner un PositionPlusAngle
        const PositionPlusAngle& operator=(const PositionPlusAngle& positionPlusAngle);

        /// @brief Surcharge d'opérateur pour comparer deux positions et angles.
        bool operator==(const PositionPlusAngle& p) const;

        /// @brief Fonction pour comparer deux positionPlusAngles à peu prés.
        bool presqueEgales(const PositionPlusAngle& positionPlusAngle) const;

        /// @brief Récupération de la position
        Position getPosition() const;

        /// @brief Envoi de la position
        void setPosition(const Position& p);

        /// @brief Récupération de l'angle
        Angle getAngle() const;

        /// @brief Pour modifier X
        void setX(Distance X);

        /// @brief Pour modifier Y
        void setY(Distance Y);

        /// @brief Envoi de l'angle
        void setAngle(Angle a);

        /// @brief position du robot par rapport à l'angle de la table
        Position position;

        /// @brief angle du robot par rapport au coté de la table
        Angle angle;

};


#endif // POSITIONPLUSANGLE_H
