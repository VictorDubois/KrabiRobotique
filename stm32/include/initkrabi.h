#ifndef INITKRABI_H
#define INITKRABI_H

#include "initialisation.h"

class InitKrabi : public Initialisation
{
public:
#ifdef ROBOTHW
    InitKrabi();
#else
    InitKrabi(bool yellow, Robot* robot);
#endif

#ifdef ROBOTHW
    virtual void setYellow();
#endif
    virtual void initClock();

// Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
// On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
    virtual void initGPIO();

    virtual void initActionneurs();
};

#endif // INITKRABI_H
