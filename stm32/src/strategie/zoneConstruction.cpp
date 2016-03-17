#include "zoneConstruction.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "position.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

ZoneConstruction::ZoneConstruction(){}

ZoneConstruction::ZoneConstruction(Position position):MediumLevelAction(position)
{

}

ZoneConstruction::~ZoneConstruction(){}

Etape::EtapeType ZoneConstruction::getType()
{
    return Etape::ZONE_CONSTRUCTION;
}

int ZoneConstruction::update()
{

    if (status == 0) //Début
    {
#ifndef ROBOTHW
        qDebug() << "Zone de construction";
#endif
        status++;
    }

    return status;
}
