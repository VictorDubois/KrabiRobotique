#include "etape.h"
#include "dijkstra.h"
#include "goldo2018.h"
#include "positionPlusAngle.h"
#include "constantes.h"
//#define ALLOW_DEBUG
#ifdef ALLOW_DEBUG
    #include "debug.h"
#endif

#define POSITIONNEMENT

#define DISABLE_TIRETTE


// Dit si on est du coté bleu
bool isBlue() // = ROUGE
{
    return true;
}

int main()
{

    Position pos(200,1850, isBlue());//1500, isBlue());
    PositionPlusAngle posPlusAngle(pos,-M_PI/2);
    if (!isBlue())
        posPlusAngle = PositionPlusAngle(pos,-M_PI/2);

    StrategieV3* strat = new Goldo2018(isBlue());

    return 0;
}
