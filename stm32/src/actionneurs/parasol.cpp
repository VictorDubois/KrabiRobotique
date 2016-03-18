#include "parasol.h"

#ifdef ROBOTHW
    #include "interfaceServosNumeriques.h"
#endif

Parasol* Parasol::getSingleton()
{
    static Parasol* instance = 0;
    if(instance == 0)
        instance = new Parasol();

    return instance;
}

Parasol::Parasol()
{
    close();
}

void Parasol::close()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(SERVO_CLOSED_POS, SERVO_ID);
#endif
}

void Parasol::deploy()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(SERVO_DEPLOYED_POS, SERVO_ID);
#endif
}
