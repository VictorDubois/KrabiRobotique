#include "CommandReculer.h"
#include "variable.h"

CommandReculer::CommandReculer() : Command()
{

}

CommandReculer::~CommandReculer()
{
    //dtor
}


Vitesse CommandReculer::getLinearSpeed()
{
    return -VITESSE_LINEAIRE_MAX/4;
}

VitesseAngulaire CommandReculer::getAngularSpeed()
{
    return 0;
}

void CommandReculer::update()
{

}
