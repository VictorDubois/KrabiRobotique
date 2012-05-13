#include "Detection.h"
#include "Arduino.h"
#include "Capteur.h"
#include "Ultrason.h"
#include "Sharp.h"

//enum sharpDetectant { AUCUN, GAUCHE, DROITE, TTAVANT, ARRIERE, TTGAUCHE, TTDROITE, TT,  AUCUNETHAUT, GAUCHEETHAUT, DROITEETHAUT, TTAVANTETHAUT, ARRIEREETHAUT, TTGAUCHEETHAUT, TTDROITEETHAUT, TTETHAUT,  AUCUNETMILIEU, GAUCHEETMILIEU, DROITEETMILIEU, TTAVANTETMILIEU, ARRIEREETMILIEU, TTGAUCHEETMILIEU, TTDROITEETMILIEU, TTETMILIEU,  AUCUNETHAUTETMILIEU, GAUCHEETHAUTETMILIEU, DROITEETHAUTETMILIEU, TTAVANTETHAUTETMILIEU, ARRIEREETHAUTETMILIEU, TTGAUCHEETHAUTETMILIEU, TTDROITEETHAUTETMILIEU, TTETHAUTETMILIEU};

//enum sharpDetectant { AUCUN, GAUCHE, DROITE, TTAVANT, ARRIERE, TTGAUCHE, TTDROITE, TT };

enum numeroSharp { GAUCHE, DROITE, MILIEU, HAUT, ARRIERE };

enum sens { AVANCER, RECULER, TOURNEGAUCHE, TOURNEDROITE, AVANCERBOUTEILLE };
/*#define pinSharpAvG  A6
#define pinSharpAvD  A4
#define pinSharpArr  A7
#define pinUltrason 10*/
#define seuilSharpAvG 350
#define seuilSharpAvD 350
#define seuilSharpMilieu 350
#define seuilSharpHaut 350
#define seuilSharpArr 350


Detection::Detection()
{
  for (int initcvqqch = 0 ; initcvqqch<NOMBRECAPTEUR ; initcvqqch++)
  {
    capteurVoitQQch[initcvqqch]=0;
    capteurVoitObstacle[initcvqqch]=0;
  }
  //int t=0;
  //Ultrason ping(10);
  
  capteurSharp = (Sharp**) malloc(sizeof( Sharp*)*NOMBRECAPTEUR);
  
  capteurSharp[GAUCHE] = new Sharp(A1, seuilSharpAvG);
  capteurSharp[DROITE] = new Sharp(A3, seuilSharpAvD);
  capteurSharp[MILIEU] = new Sharp(A5, seuilSharpMilieu);
  capteurSharp[HAUT]   = new Sharp(A4, seuilSharpHaut);
  capteurSharp[ARRIERE]= new Sharp(A6, seuilSharpArr);
  
  //Sharp capteurAvantG(A6, seuilSharpAvG), capteurAvantD(A4, seuilSharpAvD), capteurArriere(A7, seuilSharpArr);//Initialisation des 3 capteurs sharp.
  /*capteurAvantG  = new Sharp(A1, seuilSharpAvG);
  capteurAvantD  = new Sharp(A3, seuilSharpAvD);
  capteurMilieu  = new Sharp(A5, seuilSharpMilieu);//peut-etre l'inverse avec haut
  capteurHaut    = new Sharp(A4, seuilSharpHaut);//peut-etre l'inverse avec milieu
  capteurArriere = new Sharp(A6, seuilSharpArr);//Initialisation des 5 capteurs sharp.*/
  //ping = new Ultrason(t);
}

Detection::~Detection()
{

}

int Detection::JePeuxAvancer(int sensVoulu)//Utilise LireCapteursSharp pour déterminer si le robot peux avancer ou non.
{
  LireCapteursDistance();//On met à jour

  if(sensVoulu==AVANCER)
  {
    return !(capteurVoitObstacle[GAUCHE] || capteurVoitObstacle[DROITE] || capteurVoitObstacle[MILIEU]|| capteurVoitQQch[HAUT]);// || capteurVoitQQch[HAUT]);
  }
  if(sensVoulu==RECULER)
  {
    return !(capteurVoitObstacle[ARRIERE]);
  }
  if(sensVoulu==TOURNEGAUCHE)
  {
    return !(capteurVoitObstacle[GAUCHE] || capteurVoitObstacle[MILIEU]);
  }
  if(sensVoulu==TOURNEDROITE)
  {
    return !(capteurVoitObstacle[DROITE] || capteurVoitObstacle[MILIEU]);
  }
  if(sensVoulu==AVANCERBOUTEILLE)
  {
    if((capteurVoitObstacle[GAUCHE] || capteurVoitObstacle[DROITE] || capteurVoitObstacle[MILIEU]) && !capteurVoitObstacle[HAUT])
    {
      return 2;//On est à deux doigts de taper la bouteille
    }
    else
    {
      return !(capteurVoitObstacle[HAUT]);
    }
  }

}

void Detection::LireCapteursDistance()//Systeme de mémoire hystérisis : si on a vu qqch, il faut rien voir pendant 8 tours pour décider qu'il n'y a plus d'obstacle, et inversement pour voir si on n'a rien vu.
{
  for(int iLireCapteurs = GAUCHE ; iLireCapteurs<= ARRIERE ; iLireCapteurs++)
  {
    if(capteurVoitObstacle[iLireCapteurs])//Si on sait etre devant un obstacle
    {
      if(!capteurSharp[iLireCapteurs]->VoitQQch())
      {
        capteurVoitQQch[iLireCapteurs]--;//On décrémente si on ne voit rien.
      }
      else
      {
        capteurVoitQQch[iLireCapteurs]=8;//Sinon on remet le compteur à 8.
      }
      
      if(capteurVoitQQch[iLireCapteurs]==0)
      {
        capteurVoitObstacle[iLireCapteurs]=0;
      }
    }
    else//Si on n'est pas devant un obstacle
    {
      if(capteurSharp[iLireCapteurs]->VoitQQch())
      {
        capteurVoitQQch[iLireCapteurs]++;//On décrémente si on ne voit rien.
      }
      else
      {
        capteurVoitQQch[iLireCapteurs]=0;//Sinon on remet le compteur à 8.
      }
      
      if(capteurVoitQQch[iLireCapteurs]==8)
      {
        capteurVoitObstacle[iLireCapteurs]=1;
      }
    }
  }
 /* 
  capteurVoitQQch[GAUCHE]=min(8,(capteurVoitQQch[GAUCHE]+1)*capteurAvantG->VoitQQch()); 
  
  capteurVoitQQch[DROITE]=min(8,(capteurVoitQQch[DROITE]+1)*capteurAvantD->VoitQQch());

  capteurVoitQQch[MILIEU]=min(8,(capteurVoitQQch[MILIEU]+1)*capteurMilieu->VoitQQch());

  capteurVoitQQch[HAUT]=min(8,(capteurVoitQQch[MILIEU]+1)*capteurHaut->VoitQQch());

  capteurVoitQQch[ARRIERE]=min(8,(capteurVoitQQch[ARRIERE]+1)*capteurArriere->VoitQQch());*/
  
  /*capteurVoitQQch[GAUCHE]=capteurAvantG->VoitQQch();
    
  capteurVoitQQch[DROITE]=capteurAvantD->VoitQQch();

  capteurVoitQQch[MILIEU]=capteurMilieu->VoitQQch();

  capteurVoitQQch[HAUT]=capteurHaut->VoitQQch();

  capteurVoitQQch[ARRIERE]=capteurArriere->VoitQQch();*/

}
