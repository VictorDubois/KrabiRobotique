#ifndef DISTANCE_H_INCLUDED
#define DISTANCE_H_INCLUDED

#include <math.h>

/**@brief On définie Distance comme un float pour une meilleur visibilité*/
typedef float Distance;
/**@brief On définie Vitesse comme un float pour une meilleur visibilité*/
typedef float Vitesse;
/**@brief On définie Acceleration comme un float pour une meilleur visibilité*/
typedef float Acceleration;

/**@brief On vérifie qu'il y a égalité ou presque entre deux distances*/
bool DistancePresqueEgales(Distance d1, Distance d2);

#endif // DISTANCE_H_INCLUDED
