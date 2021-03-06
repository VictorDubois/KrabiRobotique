#ifndef POSITION_H
#define POSITION_H

#include "angle.h"
#include "distance.h"
#include "vec2d.h"

class StrategieV2;

#define COLOR_POSITION Position::colorPosition

/// @brief Classe permettant de stocker des positions en coordonnées cartésiennes
class Position
{
    public:

        /// @brief Constructeur par défaut avec des coordonnées nulles.
        Position();

        /// @brief Constructeur avec des coordonnées prédéfinies.
        Position(Distance X, Distance Y, bool colorDependent = false);

        Position getSymetrical();

        /// @brief Surchage d'opérateur pour ajouter des coordonnées
        Vec2d operator+(const Position &position) const;

        /// @brief Surchage d'opérateur pour soustraire des coordonnées
        Vec2d operator-(const Position &position) const;

        /// @brief Surchage d'opérateur pour multiplier par un flottant
        Position operator*(float val) const;

        static Position colorPosition(Distance x, Distance y, bool isYellow = false);

        /// @brief Surcharge d'opérateur pour assigner une position.
        void operator=(Position position);

        /// @brief Surchage d'opérateur pour ajouter et copier des coordonnées
        Position operator+=(const Position &position);

        /// @brief Surchage d'opérateur pour soustraire et copier des coordonnées
        Position operator-=(const Position &position);

        /// @brief Surchage d'opérateur pour multiplier les coordonées
        bool operator*=(float val);

        /// @brief Surchage d'opérateur pour comparer des coordonnées
        bool operator==(const Position &p) const;

        /// @brief Surchage d'opérateur pour ajouter des coordonnées
        Position operator+(const Vec2d &vec2d) const;

        /// @brief Surchage d'opérateur pour soustraire des coordonnées
        Position operator-(const Vec2d &vec2d) const;

        /// @brief Fonction comparant l'égalité de positions à peu prés
        bool presqueEgales(const Position &p) const;

        /// @brief Fonction donnant la distance entre la position et le point de coordonnées nulles
        Distance getNorme(void) const;

        /// @brief Fonction donnant l'angle entre l'axe des absysses et la position
        Angle getAngle(void) const;

        /// @brief Pour récupérer X
        Distance getX() const;

        /// @brief Pour récupérer Y
        Distance getY() const;

        /// @brief Pour modifier X
        void setX(Distance X);

        /// @brief Pour modifier Y
        void setY(Distance Y);

        /// @brief Coordonnées
        Distance x;
        Distance y;
};

#endif
