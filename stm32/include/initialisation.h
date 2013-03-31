#ifndef INITIALISATION_H
#define INITIALISATION_H

// Initialise le système d'horloge
void Clk_Init();

// Définit quelques horloges supplémentaires
void initAutresHorloges();

// Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
// On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
void initialisationDesPIN();

#endif // INITIALISATION_H
