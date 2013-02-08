#include "angle.h"
#include <math.h>

// Retourne la valeur de l'angle dans un float entre -PI et PI.
Angle wrapAngle(Angle angle)
{
    static const Angle M_2PI = 6.283185307179586476925;

    if (angle > 0)
    {
        while (angle > M_PI)
            angle -= M_2PI;
    }
    else
    {
        while (angle < -M_PI)
            angle += M_2PI;
    }
    return angle;
}

// Vérifie s'il y a égalité ou presque entre deux angles.
bool angleEq(Angle a1, Angle a2)
{
    static const Angle epsilon = 0.1;
    return (fabs(wrapAngle(a1 - a2)) < epsilon);
}
