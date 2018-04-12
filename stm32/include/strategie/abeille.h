#ifndef ABEILLE_H
#define ABEILLE_H

#include "position.h"
#include "mediumLevelAction.h"

#ifndef STANDALONE_STRATEGIE
#include "command.h"
#endif // STANDALONE_STRATEGIE

class Abeille : public MediumLevelAction
{
public:
    Abeille();

    Abeille(Position position);

    ~Abeille();

    int update();

    Etape::EtapeType getType();

protected:
    Position position;
    Position position_depart;
};

#endif // ABEILLE_H
