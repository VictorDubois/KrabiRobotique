#include "variable.h"
#include "actionChercherPiece.h"
int abs(int x)
{
    return (x>=0)? x:-x;
}

bool intersectionDeuxSegments(Position a,Position b,Position c,Position d)
{
    // cherche une solution (t,u) avec 0.0f <= t,u <= 1.0f au système
        // xa+t*(xb-xa) = xc+u*(xd-xc)
        // ya+t*(yb-ya) = yc+u*(yd-yc)

        // determinant
        Distance det = (d.x-c.x)*(b.y-a.y)-(b.x-a.x)*(d.y-c.y);

        // unique solution (t,u)
        if (det != 0.0f)
        {
                Distance u = ((a.x-c.x)*(b.y-a.y)-(a.y-c.y)*(b.x-a.x))/det;
                if (0.0f <= u && u <= 1.0f)
                {
                        Distance t = ((c.x-a.x)*(d.y-c.y)-(c.y-a.y)*(d.x-c.x))/det;
                        return (0.0f <= t && t <= 1.0f);
                }
                else
                {
                        return false;
                }
        }

        // les lignes sont paralleles
        else
        {
                // approximation : faux en général
                return false;
        }
}

const Distance gaucheTotem = 975-RAYON_ROBOT;
const Distance droiteTotem = 2025+RAYON_ROBOT;
const Distance hautTotem = 1125+RAYON_ROBOT;
const Distance basTotem = 875-RAYON_ROBOT;


bool intersectionTotem(Position positionInitiale,Position positionFinale)
{
    // bord du totem

    const Position nordOuest(gaucheTotem,hautTotem);
    const Position sudOuest(gaucheTotem,basTotem);
    const Position nordEst(droiteTotem,hautTotem);
    const Position sudEst(droiteTotem,basTotem);
    return (intersectionDeuxSegments(positionInitiale,positionFinale,nordOuest,sudEst) ||
        intersectionDeuxSegments(positionInitiale,positionFinale,sudOuest,nordEst));
}


const Distance gauchePosInt= gaucheTotem-150;
const Distance droitePosInt= droiteTotem+150;
const Distance hautPosInt= hautTotem+150;
const Distance basPosInt= basTotem -150;
const Position hautDroite(droitePosInt,hautPosInt);
const Position basDroite(droitePosInt,basPosInt);
const Position hautGauche(gauchePosInt,hautPosInt);
const Position basGauche(gauchePosInt,basPosInt);

ActionChercherPiece::ActionChercherPiece(Position destinationFinale,Odometrie* odometrie, bool is_Blue)
:destinationFinale(destinationFinale),odometrie(odometrie),numeroPositionSuivante(1)
{
    Position pos(odometrie->getPos().getPosition());
    if(intersectionTotem(pos,destinationFinale))
    {
        int xid =0, yid = 0, xia = 0, yia = 0;
        if (pos.x<gaucheTotem) xid=-1;
        else if (pos.x>droiteTotem) xid=1;
        if (pos.y<basTotem) yid=-1;
        else if (pos.y<hautTotem) yid=1;
        if (destinationFinale.x<gaucheTotem) xia=-1;
        else if (destinationFinale.x>droiteTotem) xia=1;
        if (destinationFinale.y<basTotem) yia=-1;
        else if (destinationFinale.y<hautTotem) yia=1;

        int d = 0;
        if ((xid==0 && xia==0) || (yid==0 && yia==0))
            d = 4;
        else d = abs(xia-xid)+abs(yia-yid);

        switch (d)
        {
            case 2:
                nbPositionIntermediaire = 1;
                if ((xia==1 && yid==-1) || (xid==1 && yia==-1))
                    positionIntermediaireUn = basDroite;
                else if ((xia==1 && yid==1) || (xid==1 && yia==1))
                    positionIntermediaireUn = hautDroite;
                else if ((xia==-1 && yid==1) || (xid==-1 && yia==1))
                    positionIntermediaireUn = hautGauche;
                else if ((xia==-1 && yid==-1) || (xid==-1 && yia==-1))
                    positionIntermediaireUn = basGauche;
                positionIntermediaire = positionIntermediaireUn;
                break;

            case 3:
                nbPositionIntermediaire = 1;
                if(xid + yid > -1 && xia+yia > -1)
                    positionIntermediaireUn = hautDroite;
                else if(xid + yid < 1 && xia+yia < 1)
                    positionIntermediaireUn = basGauche;
                else if(xid - yid > -1 && xia-yia > -1)
                    positionIntermediaireUn = basDroite;
                else if(xid - yid < 1 && xia-yia < 1)
                    positionIntermediaireUn = hautGauche;
                positionIntermediaire = positionIntermediaireUn;
                break;
            case 4:
                if (xia == 0 || yia == 0)
                {
                    nbPositionIntermediaire = 2;
                    if(xia==0 && yia==-1)
                    {
                        positionIntermediaireUn = is_Blue? basGauche:basDroite;
                        positionIntermediaireDeux = is_Blue? hautGauche:hautDroite;
                    }
                    else if(xia==0 && yia==1)
                    {
                        positionIntermediaireUn = is_Blue? hautGauche:hautDroite;
                        positionIntermediaireDeux = is_Blue? basGauche:basDroite;
                    }
                    else if(yia==0 && xia==-1)
                    {
                        positionIntermediaireUn = hautGauche;
                        positionIntermediaireDeux = hautDroite;
                    }
                    else if(yia==0 && xia==1)
                    {
                        positionIntermediaireUn = hautDroite;
                        positionIntermediaireDeux = hautGauche;
                    }
                }
                else
                {
                    nbPositionIntermediaire = 1;
                    if(abs(xia+yia)==2) positionIntermediaireUn = is_Blue? hautGauche:basDroite;
                    else if(abs(xia-yia)==2) positionIntermediaireUn = is_Blue? basGauche:hautDroite;
                }
                break;
            default:
                break;

        }
    }
    else
    {
        nbPositionIntermediaire = 0;
        positionIntermediaire = destinationFinale;

    }
    commandActuelle=new CommandGoTo(positionIntermediaire);
}
ActionChercherPiece::~ActionChercherPiece()
{
}

//renvoie true si l'action est finie
bool ActionChercherPiece::executer()
{
    Position trajet(positionIntermediaire-odometrie->getPos().getPosition());
    float d = trajet.x*trajet.x+trajet.y*trajet.y;
    float e =  30.0f*30.0f;
    if(d<e)
    //le robot est a moins de 3cm du point intermediaire
    {
        switch (nbPositionIntermediaire-numeroPositionSuivante)
        {
        case 0:
            return true;
            break;
        case 1:
            new CommandGoTo(destinationFinale);
            break;
        default :
            if(numeroPositionSuivante==1)
                new CommandGoTo(positionIntermediaireUn);
            else
                new CommandGoTo(positionIntermediaireDeux);
        }
    }
    return false;
}
