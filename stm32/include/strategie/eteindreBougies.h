#ifndef ETEINDREBOUGIES_H
#define ETEINDREBOUGIES_H

#include "mediumLevelAction.h"
#include "eteindreBougieV2.h"

class EteindreBougies : public MediumLevelAction
{
    public:
        EteindreBougies(bool isBlue);
        virtual ~EteindreBougies();
        
        virtual int update();
    protected:
    private:
        EteindreBougieV2* bougiesBas[12];
        EteindreBougieV2* bougiesHaut[8];
        int etapeBas;
        bool bleuVersRouge; // si le robot va du bleu vers le rouge quand il fait le gateau
};

#endif // ETEINDREBOUGIES_H
