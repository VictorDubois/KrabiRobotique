#include "action.h"
int abs(int x)
{
    return (x>=0)? x:-x;
}



ActionBase::ActionBase()
    : position(), reculer(false)
{
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

const Distance gaucheTotem = -525-RAYON_ROBOT;
const Distance droiteTotem = 525+RAYON_ROBOT;
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

class ActionSuivreChemin : public Action
{
    ActionBase* chemin;
    int taille;
    int pointSuivant;
    Odometrie* odometrie;
    public:
        ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo)
        :   chemin(NULL), taille(n), pointSuivant(0), odometrie(odo)
        {
            if (n != 0)
                chemin = new ActionBase[n];

            for(int i = 0; i < n; i++)
                chemin[i] = tab[i];

        }

        ~ActionSuivreChemin()
        {
            if (chemin != NULL)
                delete[] chemin;
        }

        virtual bool executer()
        {
            if (taille ==0)
                return true;

            Position trajet(chemin[pointSuivant].position-odometrie->getPos().getPosition());

            if(trajet.x*trajet.x+trajet.y*trajet.y < 30.0f*30.0f || pointSuivant == 0)
            {
                pointSuivant++;
                if (pointSuivant < taille)
                    new CommandGoTo(chemin[pointSuivant].position);
            }

            return (pointSuivant >= taille);

        }


};

ListeDActions::ListeDActions(Odometrie* odo)
    : actionActuelle(NULL), actions(NULL), nbActions(0), odom(odo), nbActionsBase(NULL)
{
    initialiserTableauDeBase();
}

ListeDActions::~ListeDActions()
{
    if (actions!=NULL)
    {
        for(int i=0;i<nbActions;i++)
            delete[] actions[i];
        delete[] actions;
    }

    if (nbActionsBase!=NULL)
        delete[] nbActionsBase;

    if ( actionActuelle != NULL)
        delete actionActuelle;

}

void ListeDActions::ajouter(ActionBase* actionBase)
{
    if (nbActions<nbActionsMax)
    {
        actions[nbActions]=actionBase;
        nbActions++;
    }
}

void  ListeDActions::initialiserTableauDeBase()
{
    actions=new ActionBase*[nbActionsMax];
    nbActionsBase = new int[nbActionsMax];
    for(int i = 0 ; i < nbActionsMax ; i++)
        nbActionsBase[i] = 0;

    actions[0]=new ActionBase[4];
    actions[0][0].position = Position(500,1500);//1
    actions[0][1].position = Position(1100,1215);//2
    actions[0][2].position = Position(1200,1000);//3
    actions[0][3].position = Position(860,1215);//3b
    actions[0][3].reculer = true; // a reculon
    nbActionsBase[0] = 4;


/*    actions[0]=new ActionBase[1];
    actions[0][0].position = Position(1500,500);//1
    nbActionsBase[0] = 2;
*/

    actions[1]=new ActionBase[8];
    actions[1][0].position = Position(860,600);//3c
    actions[1][1].position = Position(175,450);//3d
    actions[1][2].position = Position(0,647);//4
    actions[1][3].position = Position(230,830);//5
    actions[1][4].position = Position(400,760);//6
    actions[1][5].position = Position(570,830);//7
    actions[1][6].position = Position(1200,1300);//8
    actions[1][7].position = Position(860,1000);//9
    actions[1][7].reculer = true; // a reculon
    nbActionsBase[1] = 8;


    nbActions=1;
}

void ListeDActions::supprimerPremiereAction()
{
    if (nbActions!=0)
    {
        delete actions[0];
        for(int i=0;i<nbActions;i++)
        {
            actions[i]=actions[i+1];
            nbActionsBase[i] = nbActionsBase[i+1];
        }
        nbActions--;
    }
}

Action* ListeDActions::creerPremiereAction()
{
    if (actionActuelle != NULL)
        delete actionActuelle;

    actionActuelle = new ActionSuivreChemin(actions[0], nbActionsBase[0],odom);
    return actionActuelle;
}

Action* ListeDActions::getActionActuelle()
{
    return actionActuelle;
}

void ListeDActions::reordonnerSerieDAction(int n)
{
    if(n>=nbActionsMax)
    return;
    ActionBase** nouveau=new ActionBase*[nbActionsMax];
    for(int i=n;i<nbActions;i++)
    {
        nouveau[i-n]=actions[i];
    }
    for(int i=0;i<n;i++)
    {
        nouveau[i+n]=actions[i];
    }
    delete[] actions;
    actions=nouveau;
}
