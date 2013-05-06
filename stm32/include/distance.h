#ifndef DISTANCE_H
#define DISTANCE_H

/// @brief On définie Distance comme un float pour une meilleur lisibilité
typedef float Distance;

/// @brief On définie Vitesse comme un float pour une meilleur lisibilité
typedef float Vitesse;

/// @brief On définie Acceleration comme un float pour une meilleur lisibilité
typedef float Acceleration;

/// @brief On vérifie qu'il y a égalité ou presque entre deux distances
bool distancePresqueEgales(Distance d1, Distance d2);

#define abs(x) x>0?x:-x

#endif // DISTANCE_H
