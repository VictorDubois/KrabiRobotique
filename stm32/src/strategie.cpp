#include "strategie.h"


Strategie* Strategie::strategie = NULL;

Strategie::Strategie(bool is_blue, Odometrie* odometrie) :
collision_detected(false)
{
    this->is_blue = is_blue;
    this->odometrie = odometrie;
    strategie = this;
    Position positionDeDepart(POS_DEPART_X,POS_DEPART_Y);
    Angle angleDeDepart(0);

    positionDeDepart.setY(positionDeDepart.getY()*(is_blue ? 1:-1));
    angleDeDepart = angleDeDepart*(is_blue ? 1:-1);
    //command = new Asservissement(PositionPlusAngle(Position(335, 400), Angle(M_PI_2)), roueCodeuseGauche, roueCodeuseDroite);
    odometrie->setPos(PositionPlusAngle(positionDeDepart,angleDeDepart));
    //command = new Asservissement(PositionPlusAngle(positionDeDepart, angleDeDepart), roueCodeuseGauche, roueCodeuseDroite);
    //command = new Asservissement(PositionPlusAngle(Position(0, 0), Angle(0)), roueCodeuseGauche, roueCodeuseDroite);
    //command->strategie = this;
    instruction_nb=1;
    doNthInstruction(instruction_nb);
}

void Strategie::done(){
    //Si tout est ok, on passe à la suite
    if(!collision_detected){
        instruction_nb++;
        doNthInstruction(instruction_nb);
    }
    else{   //Sinon on fait les instructions au dessus de 128 (Pas utilisé ici)
        instruction_collision_nb++;
        doNthInstruction(INSTRUCTION_COLLISION+instruction_collision_nb);
    }

}

void Strategie::collisionDetected(){
    collision_detected = true;
    instruction_collision_nb=0;
    doNthInstruction(INSTRUCTION_COLLISION);
}


void Strategie::doNthInstruction(uint16_t n){
   int cote = (is_blue ? 1:-1);

    /*switch(n) {
        case 1:
                (new TrapezoidalCommand)->goTo(Position(500, cote*250),true);
        break;
        case 2:
                (new TrapezoidalCommand)->goTo(Position(1000, cote*450),true);
        break;
        case 3:
               (new TrapezoidalCommand)->goTo(Position(1500, cote*275),true);
        break;
        case 4:
                (new TrapezoidalCommand)->goTo(Position(1300, cote*300),true);
        break;
        case 5:
               (new TrapezoidalCommand)->goTo(Position(2000, cote*500),true);
        break;
        case 6:
                (new TrapezoidalCommand)->goTo(Position(1000, cote*650),true);
        break;
        case 7:
                (new TrapezoidalCommand)->goTo(Position(400, cote*750),true);
        break;
        case 8:
                (new TrapezoidalCommand)->goTo(Position(650,cote*900),true);

        break;
      case 9:
           //     (new TrapezoidalCommand)->goTo(Position(650,cote*1000),true);
        break;*/
     /*   case 10:
                (new TrapezoidalCommand)->goTo(Position(1420,cote*1200),true);
        break;
        case 11:
                (new TrapezoidalCommand)->goTo(Position(1420,cote*1050),true);
        break;
   /*     case 12:
   //             (new TrapezoidalCommand)->goTo(Position(720,cote*1730),true);
        break;
        case 13:
                (new TrapezoidalCommand)->goTo(Position(1820,cote*680),true);
        break;
        case 14:
                (new TrapezoidalCommand)->goTo(Position(1980,cote*1450),true);
        break;
        case 15:
                (new TrapezoidalCommand)->goTo(Position(2050,cote*1700),true);
        break;
        case 16:
                (new TrapezoidalCommand)->goTo(Position(1000,cote*300),true);
        break;
        case 17:
                (new TrapezoidalCommand)->goTo(Position(1000,cote*1400),true);
       break;
      	default:
	break;


*/
	}

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

const Distance gaucheTotem = ;//a definir
const Distance droiteTotem = ;
const Distance hautTotem = ;
const Distance basTotem = ;

bool intersectionTotem(Position positionInitiale,Position positionFinale)
{
    // bord du totem

    const Position nordOuest(gauche,haut);
    const Position sudOuest(gauche,bas);
    const Position nordEst(droite,haut);
    const Position sudEst(droite,bas);
    return (intersectionDeuxSegments(positionInitiale,positionFinale,nordOuest,sudEst) ||
        intersectionDeuxSegments(positionInitiale,positionFinale,sudOuest,nordEst));
}

ListeDActions::ListeDActions()
    : actions(NULL), nbActions(0)
{
    initialiserTableauDeBase();
}

ListeDActions::~ListeDActions()
{
    if (actions!=NULL)
    {
        for(int i =0 ; i < nbActions ; i++)
            delete actions[i];
        delete[] actions;
    }
}

void ListeDActions::ajouter(Action* action_ptr)
{
if (nbActions<nbActionsMax)
    {
    listeDActions(nbActions)=action_ptr;
    nbActions++;
    }
}
void  ListeDActions::initialiserTableauDeBase()
{
    actions=new Actions*[nbActionsMax];

}

class CommandChercherPiece :public Command
{
    private:
    Position destinationFinale;
    Odometrie* odometrie;
    CommandGoTo* commandActuelle;
    Position positionIntermediaire;
    int nbPositionIntermediaire;
    int numeroPositionSuivante;
    Position positionIntermediaireUn;
    Position positionIntermediaireDeux;

    const Distance gauchePosInt= ;//il faudra penser a ne pas oublier de les definir plus tard
    const Distance droitePosInt= ;
    const Distance hautPosInt= ;
    const Distance basPosInt= ;
    const Position hautDroite(droitePosInt,hautPosInt);
    const Position basDroite(droitePosInt,basPosInt);
    const Position hautGauche(gauchePosInt,hautPosInt);
    const Position basGauche(gauchePosInt,basPosInt);
    public:
    CommandChercherPiece(Position destinationFinale,Odometrie* odometrie)
    :destinationFinale(destinationFinale),odometrie(odometrie),numeroPositionSuivante(1)
    {
        Position pos(odometrie->getpos().getPosition());
        if(intersectionTotem(pos,destinationFinale))
        {
            if(pos.x>gaucheTotem&&pos.x<droiteTotem&&destinationFinale.x<droiteTotem&&destinationFinale.x>gaucheTotem)
            {
                nbPositionIntermediaire=3;
                if(pos.x<basTotem)
                {
                    positionIntermediaireUn=new(basDroite);
                    positionIntermediaireDeux=new(hautdroite);
                }
                else
                {
                    positionIntermediaireUn=new(hautdroite);
                    positionIntermediaireDeux=new(basDroite);
                }
            }
            else //niark niark niark il nous reste bcp de boulot
            positionIntermediaireUn=
        }
        else
        {
        commandActuelle=new CommandGoTo(positionIntermediaire);
        }
    }
    ~CommandChercherPiece()
    {
        if (commandActuelle!=NULL)
        delete commandActuelle;
    }

    virtual void update()
    {
        Position trajet(positionIntermediaire-odometrie->getpos().getPosition());
        if(trajet.x*trajet.x+trajet.y*trajet.y<30.0f*30.0f)
        //le robot est a moins de 3cm du point intermediaire
        {
            switch (nbPositionIntermediaire-numeroPositionSuivante)
            {
            case 0:
                delete commandActuelle;
                commandActuelle=NULL;
                break;
            case 1:
                new CommandGoTo(destinationFinale);
                break;
            default :
                if(numeroPositionSuivante=1)
                    new CommandGoTo(positionIntermediaireUn);
                else
                    new CommandGoTo(positionIntermediaireDeux);
            }
        }
        //commandActuelle->update(); appellé automatiquement dans l'asservissement
    }
};

void ListeDActions::supprimerPremiereAction()
{
    if (nbActions!=0)
    {
        delete actions[0];
        for(int i=0;i<nbActions;i++)
        {
            actions[i]=actions[i+1];
        }
        nbActions--;
    }
}

Action* ListeDActions::premiereAction()
{
    return actions[0];
}

void ListeDActions::reordonnerSerieDAction(int n)
{
    if(n>=nbActionsMax)
    return;
    Action** nouveau=new Action*[nbActionsMax];
    for(int i=n;i<nbActions;i++)
    {
        nouveau[i-n]=actions[i];
    }
    for(int i=0;i<n;i++)
    {
        neauveau[i+n]=actions[i];
    }
    delete[] actions;
    actions=nouveau;
}
