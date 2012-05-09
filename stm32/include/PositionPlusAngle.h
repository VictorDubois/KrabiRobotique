#ifndef POSITIONPLUSANGLE_H_INCLUDED
#define POSITIONPLUSANGLE_H_INCLUDED

#include "Position.h"
#include "Angle.h"
#include <math.h>

/**@brief Classe permettant d'avoir la position du robot par rapport à l'angle de la table et son angle par rapport à l'absisse. */
class PositionPlusAngle
{
    public:
        /**@brief Constructeur de la classe.
         *@param Position pos est la position du robot au moment ou l'on déclare la classe
         *@param Angle ang est l'angle du robot au moment ou l'on déclare la classe. */
        PositionPlusAngle(Position pos, Angle ang);
        /**@brief Constructeur par défault de la classe. */
        PositionPlusAngle() { }
        /**@brief Surcharge d'opérateur pour ajouter une distance. */
        PositionPlusAngle operator+(const Distance &distance);
        /**@brief Surcharge d'opérateur pour ajouter deux PositionPlusAngle (chaque paramètre deux à deux). */
        PositionPlusAngle operator+(PositionPlusAngle &posAngAdd);
        /**@brief Surcharge d'opérateur pour enlever une distance. */
        PositionPlusAngle operator-(const Distance &distance);
        /**@brief Surcharge d'opérateur pour assigner un PositionPlusAngle */
        PositionPlusAngle operator=(const PositionPlusAngle &positionPlusAngle);
        /**@brief Surcharge d'opérateur pour comparer deux positions et angles. */
        bool operator==(PositionPlusAngle &p);
        /**@brief Constructeur de copie. */
        PositionPlusAngle(const PositionPlusAngle &original);
        /**@brief Fonction pour comparer deux positionPlusAngles à peu prés. */
        bool presqueEgales(PositionPlusAngle &positionPlusAngle);
        /**@brief Récupération de la position */
        Position getPosition();
        /**@brief Envoi de la position */
        void setPosition(Position p);
        /**@brief Récupération de l'angle */
        Angle getAngle();
        /**@brief Envoi de l'angle */
        void setAngle(Angle a);
        /**@brief position du robot par rapport à l'angle de la table */
        Position position;
        /**@brief angle du robot par rapport au coté de la table */
        Angle angle;
    private:

};


#endif // POSITIONPLUSANGLE_H_INCLUDED
