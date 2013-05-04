#ifndef MARTEAUX_H_INCLUDED
#define MARTEAUX_H_INCLUDED

#define MARTEAU_BAS_GAUCHE_ID 0x0d
#define MARTEAU_BAS_GAUCHE_RELEVE_ANGLE 0x02a0
#define MARTEAU_BAS_GAUCHE_ENFONCE 0x0300
#define MARTEAU_BAS_GAUCHE_RANGE 0x01e0
#define MARTEAU_BAS_GAUCHE_VITESSE_DESCENTE 0x03ff
#define MARTEAU_BAS_GAUCHE_VITESSE_MONTEE 0x0600
#define MARTEAU_BAS_GAUCHE_VITESSE_RANGEMENT 0x0500 // vitesse assez lente quand on veut le ranger, on est pas pressés 

#define MARTEAU_HAUT_GAUCHE_ID 0x0c
#define MARTEAU_HAUT_GAUCHE_RELEVE_ANGLE 0x0090
#define MARTEAU_HAUT_GAUCHE_ENFONCE 0x00d0
#define MARTEAU_HAUT_GAUCHE_RANGE 0x01e0 
#define MARTEAU_HAUT_GAUCHE_VITESSE_DESCENTE 0x03ff
#define MARTEAU_HAUT_GAUCHE_VITESSE_MONTEE 0x0600
#define MARTEAU_HAUT_GAUCHE_VITESSE_RANGEMENT 0x0100  

#define MARTEAU_HAUT_DROIT_ID 0x0b
#define MARTEAU_HAUT_DROIT_RELEVE_ANGLE 0x03a0
#define MARTEAU_HAUT_DROIT_ENFONCE 0x0340
#define MARTEAU_HAUT_DROIT_RANGE 0x0280 
#define MARTEAU_HAUT_DROIT_VITESSE_DESCENTE 0x07ff
#define MARTEAU_HAUT_DROIT_VITESSE_MONTEE 0x0200
#define MARTEAU_HAUT_DROIT_VITESSE_RANGEMENT 0x0500  

#define MARTEAU_BAS_DROIT_ID 0x0a
#define MARTEAU_BAS_DROIT_RANGE 0x01f8
#define MARTEAU_BAS_DROIT_ENFONCE 0x00c0
#define MARTEAU_BAS_DROIT_RELEVE_ANGLE 0x0170
#define MARTEAU_BAS_DROIT_VITESSE_DESCENTE 0x07ff
#define MARTEAU_BAS_DROIT_VITESSE_MONTEE 0x0200
#define MARTEAU_BAS_DROIT_VITESSE_RANGEMENT 0x0100 

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
