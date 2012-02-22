#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED

#include <math.h>

/**@brief On définie un Angle comme étant un double pour que l'on comprenne mieux le programme. */
typedef float Angle;
typedef float VitesseAngulaire;
typedef float AccelerationAngulaire;

/**@brief Retourne la valeur de l'angle dans un float entre -PI et PI. */
float wrapAngle(Angle angle);
/**@brief Vérifie s'il y a égalité ou presque entre deux angles. */
bool angleEq(Angle a1, Angle a2);
/**@brief Approximation de la fonction sinus car la fonction sinus de math.h block à l'execution */
float sinx(Angle x);
/**@brief Approximation de la fonction cosinus car la fonction cosinus de math.h block à l'execution */
float cosx(Angle x);

#endif // ANGLE_H_INCLUDED

