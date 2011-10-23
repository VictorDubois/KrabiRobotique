#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED

#include <math.h>

/**@brief On définie un Angle comme étant un double pour que l'on comprenne mieux le programme. */
typedef double Angle;

/**@brief Retourne la valeur de l'angle dans un float entre -PI et PI. */
float wrapAngle(Angle angle);
/**@brief Vérifie s'il y a égalité ou presque entre deux angles. */
bool angleEq(Angle a1, Angle a2);

#endif // ANGLE_H_INCLUDED

