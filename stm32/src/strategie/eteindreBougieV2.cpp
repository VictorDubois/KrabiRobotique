#include "eteindreBougieV2.h"
#include "odometrie.h"

EteindreBougieV2::EteindreBougieV2()
{
    //ctor
}

EteindreBougieV2::~EteindreBougieV2()
{
    //dtor
}

int EteindreBougieV2::update()
{
    if (status == 0)
        status = 1;

    if (status == 1)
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        float distance = vect.getNorme();
        if (distance < 20.0)
        {
            status = 2;
        }
    }
    else if (status == 500)
    {
        status = -1;
    }
    else
        status++;

    return status;

}
