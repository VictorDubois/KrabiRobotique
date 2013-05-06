#ifndef MARTEAUX_H_INCLUDED
#define MARTEAUX_H_INCLUDED

// MBG : marteau bas gauche
#define MBG_ID 0x0d
#define MBG_RELEVE 0x02c0
#define MBG_ENFONCE 0x0330
#define MBG_RANGE 0x0200
#define MBG_VITESSE_DESCENTE 0x03ff
#define MBG_VITESSE_MONTEE 0x0600
#define MBG_VITESSE_RANGEMENT 0x0500 // vitesse assez lente quand on veut le ranger, on est pas pressés

// MHG : marteau haut gauche
#define MHG_ID 0x0c
#define MHG_RELEVE 0x0090
#define MHG_ENFONCE 0x0100
#define MHG_RANGE 0x01e0
#define MHG_VITESSE_DESCENTE 0x03ff
#define MHG_VITESSE_MONTEE 0x0600
#define MHG_VITESSE_RANGEMENT 0x0100

// marteau haut droit
#define MHD_ID 0x0b
#define MHD_RELEVE 0x03a0
#define MHD_ENFONCE 0x0330
#define MHD_RANGE 0x0240
#define MHD_VITESSE_DESCENTE 0x07ff
#define MHD_VITESSE_MONTEE 0x0200
#define MHD_VITESSE_RANGEMENT 0x0500

// marteau bas droit
#define MBD_ID 0x0a
#define MBD_RANGE 0x01f8
#define MBD_ENFONCE 0x00c0
#define MBD_RELEVE 0x0140
#define MBD_VITESSE_DESCENTE 0x07ff
#define MBD_VITESSE_MONTEE 0x0200
#define MBD_VITESSE_RANGEMENT 0x0100

namespace Marteaux
{
    void enfoncerHautGauche();
    void releverHautGauche();
    void rangerHautGauche();

    void enfoncerBasGauche();
    void releverBasGauche();
    void rangerBasGauche();

    void enfoncerHautDroit();
    void releverHautDroit();
    void rangerHautDroit();

    void enfoncerBasDroit();
    void releverBasDroit();
    void rangerBasDroit();
}


#endif // MARTEAUX_H_INCLUDED
