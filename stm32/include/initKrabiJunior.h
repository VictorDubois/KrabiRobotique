#ifndef INITKRABIJUNIOR_H
#define INITKRABIJUNIOR_H

#include "initialisation.h"


class InitKrabiJunior : public Initialisation
{
public:
#ifdef ROBOTHW
    InitKrabiJunior();
#else
    InitKrabiJunior(bool yellow, Robot* robot);
#endif

#ifdef ROBOTHW
    virtual void setYellow();
#endif
    virtual void initClock();

// Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
// On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
    virtual void initGPIO();

	void initRotaryEncoders();

    virtual void initActionneurs();
};

#endif // INITKRABIJUNIOR_H
