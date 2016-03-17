#include "cabine.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Cabine::Cabine(){}

Cabine::Cabine(Position position):MediumLevelAction(position)
{

}

Cabine::~Cabine(){}

Etape::EtapeType Cabine::getType()
{
    return Etape::CABINE;
}

int Cabine::update()
{

    if (status == 0) //Début
    {
#ifndef ROBOTHW
        qDebug() << "Ouverture cabine";
#endif
     status++;
    }

    return status;
}
