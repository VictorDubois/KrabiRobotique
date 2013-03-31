#ifndef ANGLE_H
#define ANGLE_H

/// @brief On définie un Angle comme étant un float pour que l'on comprenne mieux le programme.
typedef float Angle;
typedef float VitesseAngulaire;
typedef float AccelerationAngulaire;

/// @brief Retourne la valeur de l'angle dans un float entre -PI et PI.
Angle wrapAngle(Angle angle);

/// @brief Vérifie s'il y a égalité ou presque entre deux angles.
bool angleEq(Angle a1, Angle a2);

#endif // ANGLE_H

