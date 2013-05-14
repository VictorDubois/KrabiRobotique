#include "marteaux.h"
#include "interfaceServosNumeriques.h"

namespace Marteaux 
{
#ifdef ROBOTHW
    void enfoncerHautGauche()
    {
        ServosNumeriques::moveToAtSpeed(MHG_ENFONCE, MHG_VITESSE_DESCENTE, MHG_ID);
    }
    void releverHautGauche()
    {
        ServosNumeriques::moveToAtSpeed(MHG_RELEVE, MHG_VITESSE_MONTEE, MHG_ID);
    }
    void rangerHautGauche()
    {
        ServosNumeriques::moveToAtSpeed(MHG_RANGE, MHG_VITESSE_RANGEMENT, MHG_ID);
    }
    
    void enfoncerBasGauche()
    {
        ServosNumeriques::moveToAtSpeed(MBG_ENFONCE, MBG_VITESSE_DESCENTE, MBG_ID);
    }
    void releverBasGauche()
    {
        ServosNumeriques::moveToAtSpeed(MBG_RELEVE, MBG_VITESSE_MONTEE, MBG_ID);
    }
    void rangerBasGauche()
    {
        ServosNumeriques::moveToAtSpeed(MBG_RANGE, MBG_VITESSE_RANGEMENT, MBG_ID);
    }
    
    void enfoncerHautDroit()
    {
        ServosNumeriques::moveToAtSpeed(MHD_ENFONCE, MHD_VITESSE_DESCENTE, MHD_ID);
    }
    void releverHautDroit()
    {
        ServosNumeriques::moveToAtSpeed(MHD_RELEVE, MHD_VITESSE_MONTEE, MHD_ID);
    }
    void rangerHautDroit()
    {
        ServosNumeriques::moveToAtSpeed(MHD_RANGE, MHD_VITESSE_RANGEMENT, MHD_ID);
    }
    
    void enfoncerBasDroit()
    {
        ServosNumeriques::moveToAtSpeed(MBD_ENFONCE, MBD_VITESSE_DESCENTE, MBD_ID);
    }
    void releverBasDroit()
    {
        ServosNumeriques::moveToAtSpeed(MBD_RELEVE, MBD_VITESSE_MONTEE, MBD_ID);
    }
    void rangerBasDroit()
    {
        ServosNumeriques::moveToAtSpeed(MBD_RANGE, MBD_VITESSE_RANGEMENT, MBD_ID);
    }
#else
    void enfoncerHautGauche() {}
    void releverHautGauche() {}
    void rangerHautGauche() {}

    void enfoncerBasGauche() {}
    void releverBasGauche() {}
    void rangerBasGauche() {}

    void enfoncerHautDroit() {}
    void releverHautDroit() {}
    void rangerHautDroit() {}

    void enfoncerBasDroit() {}
    void releverBasDroit() {}
    void rangerBasDroit() {}
#endif
    void enfoncerMarteau(bool bas, bool gauche)
    {
        if (bas)
        {
            if (gauche)
                enfoncerBasGauche();
            else
                enfoncerBasDroit();
        }
        else
        {
            if (gauche)
                enfoncerHautGauche();
            else
                enfoncerHautDroit();
        }
    }
    void releverMarteau(bool bas, bool gauche)
    {
        if (bas)
        {
            if (gauche)
                releverBasGauche();
            else
                releverBasDroit();
        }
        else
        {
            if (gauche)
                releverHautGauche();
            else
                releverHautDroit();
        }
    }
    void rangerMarteau(bool bas, bool gauche)
    {
        if (bas)
        {
            if (gauche)
                rangerBasGauche();
            else
                rangerBasDroit();
        }
        else
        {
            if (gauche)
                rangerHautGauche();
            else
                rangerHautDroit();
        }
    }

    
}
