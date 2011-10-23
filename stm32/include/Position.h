#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#include "Angle.h"
#include "distance.h"
#include <math.h>

/**@brief Classe permettant de stocker des positions en coordonnées cartésienne */
class Position{
    public:
        /**@brief Constructeur par défaut avec des coordonnées nulles. */
        Position() { x=0; y=0; }
        /**@brief Constructeur avec des coordonnées prédéfinies. */
        Position(Distance x, Distance y);
        /**@brief Surchage d'opérateur pour ajouter des coordonnées */
        Position operator+(const Position &position);
        /**@brief Surchage d'opérateur pour soustraire des coordonnées */
        Position operator-(const Position &position);
        /**@brief Surcharge d'opérateur pour assigner une position. */
        Position operator=(const Position &position);
        /**@brief Surchage d'opérateur pour ajouter et copier des coordonnées */
        Position operator+=(const Position &position);
        /**@brief Surchage d'opérateur pour soustraire et copier des coordonnées */
        Position operator-=(const Position &position);
        /**@brief Surchage d'opérateur pour comparer des coordonnées */
        bool operator==(const Position &p);
        /**@brief Fonction comparant l'égalité de positions à peu prés */
        bool presqueEgales(const Position &p);
        /**@brief Fonction donnant la distance entre la position et le point de coordonnées nulles */
        Distance getNorme(void);
        /**@brief Fonction donnant l'angle entre l'axe des absysses et la position */
        Angle getAngle(void);
        /**@brief Pour récupérer X */
        Distance getX();
        /**@brief Pour récupérer Y */
        Distance getY();
        /**@brief Pour modifier X */
        void setX(Distance x);
        /**@brief Pour modifier Y */
        void setY(Distance y);

    private:
        /**@brief Coordonnées */
        Distance x,y;
};

#endif
