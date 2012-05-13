#include <Servo.h> 
#include "Diode.h"
#include "Detection.h"
#include <EEPROM.h>

#define AUTO 0
#define RATTRAPAGE 1


  // DEFINITION DES CONSTANTES //

const int pinRoueG = 5;
const int pinRoueD = 3;



const int pinCalClaire = 9;
const int pinCalObs = 7;
const int pinCalGD = 6;

//##### DFRduino nano
/*const int pinCCG = A0;//pin du CapteurCouleurGauche
const int pinCCD = A1;

const int pinTirr = A5;

const int pinSharpAvG = A6;
const int pinSharpAvD = A4;
const int pinSharpArr = A7;*/

//##### Arduino nano
const int pinCCG = A0;//pin du CapteurCouleurGauche
const int pinCCD = A7;

const int pinTirr = A2;

const int pinSharpAvG = A1;//attention, aussi défini dans detection
const int pinSharpAvD = A3;
const int pinSharpArr = A6;

const int pinLed1 = 8;
const int pinLed2 = 11;
const int pinLed3 = 12;

const int pinPing = 10;

enum couleurMatch { ROUGE, VIOLET };
enum sharpDetectant { AUCUN, GAUCHE, DROITE, TTAVANT, ARRIERE, TTGAUCHE, TTDROITE, TT,  AUCUNETHAUT, GAUCHEETHAUT, DROITEETHAUT, TTAVANTETHAUT, ARRIEREETHAUT, TTGAUCHEETHAUT, TTDROITEETHAUT, TTETHAUT,  AUCUNETMILIEU, GAUCHEETMILIEU, DROITEETMILIEU, TTAVANTETMILIEU, ARRIEREETMILIEU, TTGAUCHEETMILIEU, TTDROITEETMILIEU, TTETMILIEU,  AUCUNETHAUTETMILIEU, GAUCHEETHAUTETMILIEU, DROITEETHAUTETMILIEU, TTAVANTETHAUTETMILIEU, ARRIEREETHAUTETMILIEU, TTGAUCHEETHAUTETMILIEU, TTDROITEETHAUTETMILIEU, TTETHAUTETMILIEU};
enum sens { AVANCER, RECULER, TOURNEGAUCHE, TOURNEDROITE, AVANCERBOUTEILLE };
  
int couleurRobot = 0;

  //  PARAMETRES DE DEPLACEMENT AUTOMATIQUE //
  
const unsigned long dureeMatch = 89000;// 89 secondes : mieux vaut ne pas prendre de risques 
//const unsigned long dureeMatch = 9000;// 89 secondes : mieux vaut ne pas prendre de risques 
unsigned long tempDepartMatch = 0;
  
const int paramArretRoueG = 90;
const int paramArretRoueD = 90;
  
  
  const int TTDroitRoueG = 110;
const int TTDroitRoueD = 69;//70à

const int TournerGaucheRoueG = 82;
const int TournerGaucheRoueD = 82;
const int TournerGaucheTemps = 865;

const int TournerDroiteRoueG = 98;
const int TournerDroiteRoueD = 98;
const int TournerDroiteTemps = 865;

const int ReculerRoueG = 77;
const int ReculerRoueD = 110;

const int ReculerLentRoueG = 85;
const int ReculerLentRoueD = 95;







const unsigned long tempsMaxCapteurs = 10;

  //  PARAMETRES DE SUIVEUR DE LIGNE //

const int valMoyenneG = 0;
const int valMoyenneD = 0;

//pour lancer le rattrapa(ge
int seuilHautRattrapageG = 0;
int seuilHautRattrapageD = 0;
int seuilBasRattrapageG = 0;
int seuilBasRattrapageD = 0;

int basGauche=0;
int basDroite=0;
int hautGauche=0;
int hautDroite=0;

int seuilHautDifferenceRattrapageG=0;
int seuilHautDifferenceRattrapageD=0;

const int paramDiff = 2;

const int paramD = 0;
const int paramG = 0;

const int offsetD = 0;
const int offsetG = 0;

const float paramSeuilHautRattrapage = 0.99;
const float paramSeuilBasRattrapage = 1.003;


//pour arreter le rattrppage
const int tempMaxRattrappage = 1000;

int seuilHautRattrapeeG = 0;
int seuilHautRattrapeeD = 0;
int seuilBasRattrapeeG = 0;
int seuilBasRattrapeeD = 0;

const float paramSeuilHautRattrapee = 0.8;
const float paramSeuilBasRattrapee = 1.1;

  //  PARAMETRES DES SHARPS //
/*
const int seuilSharpAvG = 200;
const int seuilSharpAvD = 200;
const int seuilSharpArr = 200;*/
  
const int distanceMin = 15;





  // DEFINITION DES VARIBABLES //

Servo myservoRoueGauche;
Servo myservoRoueDroite;

int bouteilleUneAPousser=0;


  // VARIABLES DIODES //
  Diode diode1(pinLed1), diode2(pinLed2), diode3(pinLed3);
  Detection detection;

  
  
int cycleAllumeDiode1 = 0;//Nombre de cycle de boucle pendant lesquels la diode 1 doit etre allumée : permet d'avoir des diodes allumées pendant des cycles entiers, pour qu'elles soient suffisament lumineuses.
int cycleAllumeDiode2 = 0;
int cycleAllumeDiode3 = 0;

  // PROTOPTYPES DES FONCTIONS //

  void SuivreLigne();
  int DeplacementAuto(char* dir, unsigned long duree, int modeRattrappageLigne);
  void Rattrapage(char* cote);
  int LireCapteursSharp();
  void Arret();
  long microsecondsToCentimeters(long microseconds);
  int DetectionUltrason();
  int JePeuxAvancer(int sensVoulu);
  void CalibrationAuto();
  void DiodesOff();
  void DiodeOn(int numeroLed, int duree);
  void EnregistreDonnee(int adresse, int valeur);
  int LireDonnee(int adresse);



void setup() //premiere fonction appelée.
{
  // initialize serial communication:
  Serial.begin(9600);
  Serial.println(10, DEC);
  
  
  myservoRoueGauche.attach(pinRoueG,200,2400);//initialisation des servos   //100,1500 || 220,2400 
  myservoRoueDroite.attach(pinRoueD,220,2400);                              //80,1500 || 200,2400
    myservoRoueDroite.write(90);//90
  myservoRoueGauche.write(90);//90

  
  pinMode(pinTirr, INPUT);//la tirette est une entrée d'information
  pinMode(pinCalClaire, INPUT);
  pinMode(pinCalObs, INPUT);
  pinMode(pinCalGD, INPUT);
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);

  pinMode(13, OUTPUT); 
  
  
  //Initialisation de la calibration capteurs couleurs à partir de l'EEPROM
  seuilHautRattrapeeG=LireDonnee(0);
  seuilHautRattrapageG=LireDonnee(1);
  seuilHautRattrapeeD=LireDonnee(2);
  seuilHautRattrapageD=LireDonnee(3);

  seuilBasRattrapeeG=LireDonnee(4);
  seuilBasRattrapageG=LireDonnee(5);
  seuilBasRattrapeeD=LireDonnee(6);
  seuilBasRattrapageD=LireDonnee(7);
  
  seuilHautDifferenceRattrapageG=LireDonnee(8);
  seuilHautDifferenceRattrapageD=LireDonnee(9);
  
  int tirretteAJamaisEtePresente=1;
  
  while(digitalRead(pinTirr)>0 || tirretteAJamaisEtePresente)//On attend que la tirette soit tirée pour débuter le match. Il faut aussi qu'elle ait été presente (sinon le robot partirai direct si allumé sans tirrette.
  {
    //Calibration : 2 modes : automatique (les 2 interrupteurs de calib' obscure (noir) et clair (bleu) sont activés) : on lance "CalibrationAuto".
    //manuelle : seul un interrupteur de calib' (obs OU clair) est activé : on calibre le capteur gauche OU droit, selon l'interrupteur de choix.
    
    diode1.DiodeOff();
    diode2.DiodeOff();
    diode3.DiodeOff();
    DiodesOff();//On éteind les diodes qui doivent l'etre
    
    if(digitalRead(pinCalClaire)>0)
    {
      if(digitalRead(pinCalObs)>0)//calibration auto
      {
        CalibrationAuto();
        while((digitalRead(pinCalClaire)>0 || digitalRead(pinCalObs)>0) && (digitalRead(pinTirr)>0 || tirretteAJamaisEtePresente))// On attend que l'utilisateur mette le robot en attente d'une nouvelle calibration (les deux interrupteurs à l'arrt ; ou que le match commence.
        {
          //On regarde si la tirrette est là :
          if (digitalRead(pinTirr)>0)
          {
            tirretteAJamaisEtePresente=0;//Alors on n'a plus qu'à attendre que la tirrette soit tirée.
          }  
          delay(1);
        }
      }
      
      else//Calibration manuelle
      {
        if(digitalRead(pinCalGD)>0)
        {
          seuilBasRattrapeeG=paramSeuilBasRattrapee*analogRead(pinCCG);
          EnregistreDonnee(4, seuilBasRattrapeeG);
          
          seuilBasRattrapageG=paramSeuilBasRattrapage*analogRead(pinCCG);
          EnregistreDonnee(seuilBasRattrapageG, 5);
          Serial.println(analogRead(pinCCG));
          Serial.println(9);
        }

      
        else
        {
          seuilBasRattrapeeD=paramSeuilBasRattrapee*analogRead(pinCCD);
          EnregistreDonnee(6, seuilBasRattrapeeD);
          
          seuilBasRattrapageG=paramSeuilBasRattrapage*analogRead(pinCCD);
          EnregistreDonnee(7, seuilBasRattrapageD);
          Serial.println(analogRead(pinCCD));
          Serial.println(8);
        }
      }
    }
    else if(digitalRead(pinCalObs)>0)
    {
      if(digitalRead(pinCalClaire)>0)//calibration auto
      {
        CalibrationAuto();
        while((digitalRead(pinCalClaire)>0 || digitalRead(pinCalObs)>0) && digitalRead(pinTirr)>0)// On attend que l'utilisateur mette le robot en attente d'une nouvelle calibration (les deux interrupteurs à l'arrt ; ou que le match commence.
        {
          delay(1);
        }
      }

      else//Calibration manuelle
      {
        if(digitalRead(pinCalGD)>0)
        {
          seuilHautRattrapeeG=paramSeuilHautRattrapee*analogRead(pinCCG);
          EnregistreDonnee(0, seuilHautRattrapeeG);
          
          seuilHautRattrapageG=paramSeuilHautRattrapage*analogRead(pinCCG);
          EnregistreDonnee(1, seuilHautRattrapageG);
          Serial.println(analogRead(pinCCG));
          Serial.println(7);
        }
        else
        {
           seuilHautRattrapeeD=paramSeuilHautRattrapee*analogRead(pinCCD);
           EnregistreDonnee(2, seuilHautRattrapeeD);
           
           seuilHautRattrapageD=paramSeuilHautRattrapage*analogRead(pinCCD);
           EnregistreDonnee(3, seuilHautRattrapageD);
           Serial.println(analogRead(pinCCD));
           Serial.println(6);
        }
      }
    }
    
    //On regarde si la tirrette est là :
    if (digitalRead(pinTirr)>0)
    {
      tirretteAJamaisEtePresente=0;//Alors on n'a plus qu'à attendre que la tirrette soit tirée.
    }
    delay(1);
  }
  
  tempDepartMatch=millis();//Référence pour s'arreter 90s plus tard.
  
  

  //Couleur de la zone de départ.
  if(digitalRead(pinCalGD)==0)
  {
    couleurRobot = VIOLET;

  }
  else
  {
    couleurRobot = ROUGE;
  }
}  
  



void loop()//Boucle principale, appelée dès que setup() est fini.
{
  

  
  
      /*DeplacementAuto("tout droit", 10000, 2);
      Arret();
            delay(1000);
            
          DeplacementAuto("reculer", 2000, AUTO);
                Arret();
      delay(10000);*/
      
      
                                                         
    //SEQUENCE INITIALE POUR REJOINDRE LA LIGNE.


  //reculer

  DeplacementAuto("tout droit", 2500, AUTO);
  Arret();
  delay(100);

                                                            
      if(couleurRobot==VIOLET)
      {
        //tourner à droite : 
        DeplacementAuto("droite", 900, AUTO);
                                                         
      }
      else
      {
        //tourner à gauche : 
        DeplacementAuto("gauche", 900, AUTO);                                                       
      }

      
      //ttdroit
      DeplacementAuto("tout droit", 1000, AUTO);

      //VERRIFICATION QU'ON EST BIEN SUR LA LIGNE
      if(couleurRobot==VIOLET)
      {
        int ligne=DeplacementAuto("gauche", 1200, 1);

        if(ligne==10 || ligne==0)//Si on n'a pas rattrappé la ligne en tournant à droite
        {
          ligne=DeplacementAuto("droite", 2400, 1);

          if(ligne==10 || ligne==0)//Si on n'a pas rattrappé la ligne en tournant à gauche
          {
            DeplacementAuto("gauche", 1250, 1);//On se recentre et on va tout droit... en esperant que ça passe... 
          }
          else//Sinon, si on a bien rattrappé la ligne
          {
            DeplacementAuto("tout droit", 600, AUTO);
            DeplacementAuto("gauche", 400, AUTO);
          }
        }
        
        
      }
      else
      {
        int ligne=DeplacementAuto("droite", 1200, 1);

        if(ligne==10 || ligne==0)//Si on n'a pas rattrappé la ligne en tournant à droite
        {
          ligne=DeplacementAuto("gauche", 2400, 1);

          if(ligne==10 || ligne==0)//Si on n'a pas rattrappé la ligne en tournant à gauche
          {
            DeplacementAuto("droite", 1250, 1);//On se recentre et on va tout droit... en esperant que ça passe... 
          }
        }
        else//Sinon, si on a bien rattrappé la ligne
        {
          
        }
                                                              
      }
      Arret();
      delay(100);
      
                                              
        
    // SEQUENCE DE SUIVAGE DE LIGNE  //
    
   // while(!bouteilleUnePoussee)
   unsigned long tempsDepartSuivageLigne = millis();
   unsigned long tempsPasseArreteSuivreLigne = 0;
   unsigned long debutArretSuivreLigne = 0;
   unsigned long tempsMiniSuivageLigne = 8000;//Le temps minimal qu'il faut au robot pour suivre la ligne : permet de ne pas taper un robot par erreur
   unsigned long tempsActuel = 0;
   int dejaArreteSuiveurLigne = 0;
  while(!bouteilleUneAPousser)
  {
    diode1.DiodeOff();
    diode2.DiodeOff();
    diode3.DiodeOff();
    DiodesOff();//On éteind les diodes qui doivent l'etre
    tempsActuel=millis();
    if(tempsActuel<tempDepartMatch+dureeMatch)//Si le match n'est pas encore fini
    {
      //if(JePeuxAvancer(AVANCER))
      
      if(detection.JePeuxAvancer(AVANCERBOUTEILLE) && dejaArreteSuiveurLigne)//Si on sort d'une période d'arret
        {
          dejaArreteSuiveurLigne=0;
          tempsPasseArreteSuivreLigne+=tempsActuel-debutArretSuivreLigne;
        }
      if(detection.JePeuxAvancer(AVANCER))
      {   
        
        SuivreLigne();
      }
      else
      {
        if(tempsActuel-tempsDepartSuivageLigne-tempsPasseArreteSuivreLigne>tempsMiniSuivageLigne && (detection.JePeuxAvancer(AVANCERBOUTEILLE)==2))//-tempsPasseArreteSuivreLigne
        {
          bouteilleUneAPousser=1;
        }
        else
        {
          
          Arret();
          if(!dejaArreteSuiveurLigne)//si c'est le début de l'arret
          {
            dejaArreteSuiveurLigne=1;
            debutArretSuivreLigne=tempsActuel;
          }

        }
      }
    }
    else//Si le match est fini
    {
      while(1)
      {
        Arret();//on arrete tout
        delay(10);
      }
    }
    
  }
  Arret();
  delay(1000);
  DeplacementAuto("pousseBouteille", 1000, AUTO);//500
  Arret();
  delay(100);
  DeplacementAuto("reculer", 1800, AUTO);
  Arret();
  delay(500);
  
  
     if(couleurRobot==ROUGE)
      {
//tourner à droite : 
DeplacementAuto("droite", 1100, AUTO);

      }
      else
      {
        //tourner à gauche : 
        DeplacementAuto("gauche", 1100, AUTO);
                                                           
      }
      Arret();
      delay(500);
      DeplacementAuto("reculer", 800, AUTO);//5000
      Arret();
       delay(500);
      DeplacementAuto("reculer lent", 1000, AUTO);//5000
      
      /*Arret();
      delay(500);
      DeplacementAuto("tout droit", 500, AUTO);//5000
      
      Arret();
      delay(500);
      if(couleurRobot==ROUGE)
      {
        //tourner à droite : 
        DeplacementAuto("droite", 50, AUTO);
      }
      else
      {
        //tourner à gauche : 
        DeplacementAuto("gauche", 50, AUTO);

      }*/
      Arret();
      delay(500);
      //DeplacementAuto("tout droit", 6000, AUTO);//5000
      DeplacementAuto("tout droit", 7000, AUTO);
      Arret();
  delay(500);
  DeplacementAuto("reculer", 500, AUTO);//5000
  
  Arret();
  delay(500);
      if(couleurRobot==VIOLET)
      {
//tourner à droite : 
DeplacementAuto("droite", 850, AUTO);
      }
      else
      {
        //tourner à gauche : 
        DeplacementAuto("gauche", 850, AUTO);
                                                           
      }
      
      Arret();
  delay(300);
  
  

    //DeplacementAuto("tout droit", 2000, 2);
 DeplacementAuto("tout droit", 500, AUTO);
  Arret();
  delay(300);
  
  DeplacementAuto("pousseBouteille", 1000, AUTO);
      Arret();
  delay(100);
  //DeplacementAuto("reculer", 1000, AUTO);
  Arret();

  delay(1000000000);
}


//############VERSION 1##################
//marche bien, mais pas idéal : peu rapide et risque de perdre la ligne si le robot a un angle trop important avec elle.
void SuivreLigne()//Permet de se déplacer en suivant la ligne.
{
  int valCCG = analogRead(pinCCG);//valeur du CapteurCouleurGauche
  int valCCD = analogRead(pinCCD);
  

  
   //if(valCCG > seuilHautRattrapageG && valCCD < seuilBasRattrapageG)//Si la ligne est entièrement sous le capteur gauche, et pas du tout sur le capteur droit
   if(valCCG > seuilHautDifferenceRattrapageG)//Si la ligne est entièrement sous le capteur gauche, et pas du tout sur le capteur droit
  {
    myservoRoueGauche.write(90);//90
    myservoRoueDroite.write(30);//82
    
    //delay(500);
    
    //Rattrapage("gauche");//on lance la procédure de rattrapage.

    
  }
  //else if(valCCD > seuilHautRattrapageD && valCCG < seuilBasRattrapageD)//Idem
  else if(valCCD > seuilHautDifferenceRattrapageD)//Idem
  {
    myservoRoueGauche.write(150);//98
    myservoRoueDroite.write(90);//90
    //delay(500);
    //Rattrapage("droite");

  }
  else//Sinon, tout va bien
  {
    //Serial.println(00000);
    
    myservoRoueGauche.write(95);
    myservoRoueDroite.write(83);
    
    //myservoRoueGauche.write(valMoyenneG-(offsetG+valCCG)*paramG+(offsetD+valCCD)*paramD);//On fait tourner les servos, en fonction des valeurs renvoyées par les capteurs.
    //myservoRoueDroite.write(valMoyenneD-(offsetD+valCCD)*paramD+(offsetG+valCCG)*paramG);
  
  }
}


int DeplacementAuto(char* dir, unsigned long duree, int modeRattrappageLigne)//Permet de se déplacer sans la ligne. v2
{
  unsigned long tempsDebut=millis();
  
  unsigned long currentTime=millis();
  
  unsigned long delaiArret = 0;//Sile robot doit s'arreter (par exemple s'il detecte un robot adverse), il faut qu'il finisse son mouvement plus tard que prevu. 
  
  unsigned long debutArret = 0;
  
  int dejaArrete = 0;
  
  int valeurRetour = 0;
  
  while((currentTime<tempDepartMatch+dureeMatch && currentTime<tempsDebut+duree+delaiArret)+dejaArrete)//Attention à dejaArrete, ça pourrait empecher le robot de s'arreter à temps avant la fin du match...
  {
    if(modeRattrappageLigne==1)
    {
            
      if(analogRead(pinCCG) > seuilHautDifferenceRattrapageG)//valeur du CapteurCouleurGauche
      {
        Arret();
        delay(100);
        DeplacementAuto("gauche", 100, AUTO);
        Arret();
        delay(100);
        //delay(500);
        valeurRetour++;
                
        //diode3.DiodeOn(2);//Allume la diode pendant 2 cycles.
       /* digitalWrite(pinLed2,HIGH);
        delay(1000);
        digitalWrite(pinLed2,LOW);*/
      }
      if(analogRead(pinCCD) > seuilHautDifferenceRattrapageD)//valeur du CapteurCouleurGauche
      {
        Arret();
        delay(100);
        DeplacementAuto("droite", 100, AUTO);
        Arret();
        delay(100);
        //delay(500);
        valeurRetour+=2;
                
        //diode3.DiodeOn(2);//Allume la diode pendant 2 cycles.
     /*   digitalWrite(pinLed1,HIGH);
        delay(1000);
        digitalWrite(pinLed1,LOW);*/
      }
      
      if(valeurRetour>0)
      {
        return valeurRetour;
      }
    }
    /*else if(modeRattrappageLigne==2)//Si on veut se mettre en place pour pousser une 2° bouteille
    {
      detection.JePeuxAvancer(AVANCERBOUTEILLE)==2;
      return 20;
    }*/
      
  //Serial.println( dejaArrete);
  if((currentTime+tempsMaxCapteurs>tempsDebut+duree+delaiArret) && !dejaArrete)//Si le mouvement est en cours et se fini avant qu'on ait le temps de faire une boucle supplémentaire, on attend la fin du mouvement.
  {
    if(currentTime<tempsDebut+duree+delaiArret)//Si le mouvement n'aurai pas déjà du etre fini
    {
      delay(currentTime+tempsMaxCapteurs-(tempsDebut+duree+delaiArret));
    }
    
    return 10;//Le mouvement est fini.
  }
  else//Sinon, on continu le mouvement.
  {
    
    if((dir=="reculer" && detection.JePeuxAvancer(RECULER)) || (dir=="reculer lent" && detection.JePeuxAvancer(RECULER)) || (dir=="tout droit" && detection.JePeuxAvancer(AVANCER)) || (dir=="gauche" && detection.JePeuxAvancer(TOURNEGAUCHE)) || (dir=="droite" && detection.JePeuxAvancer(TOURNEDROITE)) || (dir=="pousseBouteille" && (detection.JePeuxAvancer(AVANCERBOUTEILLE)>0)))
    {


        if(dejaArrete)//Si on sort d'une période d'arret
        {
          dejaArrete=0;
          delaiArret+=millis()-debutArret;
        }
        if(dir=="reculer")
        {
          myservoRoueGauche.write(ReculerRoueG);
          myservoRoueDroite.write(ReculerRoueD);
        }
        else if(dir=="tout droit")
        {
          
          myservoRoueGauche.write(TTDroitRoueG);
          myservoRoueDroite.write(TTDroitRoueD);
        }
    
        else if(dir=="droite")
        {
          myservoRoueGauche.write(TournerDroiteRoueG);
          myservoRoueDroite.write(TournerDroiteRoueD);
        }
        else if(dir=="gauche")
        {
          myservoRoueGauche.write(TournerGaucheRoueG);
          myservoRoueDroite.write(TournerGaucheRoueD);
        }
        else if(dir=="pousseBouteille")
        {
          myservoRoueGauche.write(TTDroitRoueG);
          myservoRoueDroite.write(TTDroitRoueD);
        }
        else if(dir=="reculer lent")
        {
          myservoRoueGauche.write(ReculerLentRoueG);
          myservoRoueDroite.write(ReculerLentRoueD);
        }
    
      }

      else//Sinon, s'il y a un obstacle
      {
        Arret();
        if(!dejaArrete)//si c'est le début de l'arret
        {
          dejaArrete=1;
          debutArret=millis();
        }
        delay(1);
      }
    
  }
  
  currentTime=millis();//Le temps actuel pour le prochain tour de boucle.
  }
  
  return 0;
}



void Arret()//Arrete les moteurs.
{
  myservoRoueGauche.write(paramArretRoueG);
  myservoRoueDroite.write(paramArretRoueD);
}



void CalibrationAuto()//Permet d'auto-calibrer le robot. Il faut le placer sur une ligne noire et enclencher les deux interrupteurs "cal obsc" et "cal clair".
{
  Arret();
  delay(500);
  
  //On est sensé etre sur la ligne noire, donc on calibre.
  hautGauche=analogRead(pinCCG);
  hautDroite=analogRead(pinCCD);
  
  seuilHautRattrapeeG=paramSeuilHautRattrapee*analogRead(pinCCG);
  EnregistreDonnee(0, seuilHautRattrapeeG);
  
  seuilHautRattrapageG=paramSeuilHautRattrapage*analogRead(pinCCG);
  EnregistreDonnee(1, seuilHautRattrapageG);
  
  seuilHautRattrapeeD=paramSeuilHautRattrapee*analogRead(pinCCD);
  EnregistreDonnee(2, seuilHautRattrapeeD);
  
  seuilHautRattrapageD=paramSeuilHautRattrapage*analogRead(pinCCD);
  EnregistreDonnee(3, seuilHautRattrapageD);
  delay(300);
  //On avance, pour arriver sur du blanc, puis on calibre.
  myservoRoueGauche.write(95);
  myservoRoueDroite.write(85);
  delay(500);
  Arret();
  delay(1000);
  
  basGauche=analogRead(pinCCG);
  basDroite=analogRead(pinCCD);
  
  seuilBasRattrapeeG=paramSeuilBasRattrapee*analogRead(pinCCG);
  EnregistreDonnee(4, seuilBasRattrapeeG);
  
  seuilBasRattrapageG=paramSeuilBasRattrapage*analogRead(pinCCG);
  EnregistreDonnee(5, seuilBasRattrapageG);
  
  seuilBasRattrapeeD=paramSeuilBasRattrapee*analogRead(pinCCD);
  EnregistreDonnee(6, seuilBasRattrapeeD);
  
  seuilBasRattrapageD=paramSeuilBasRattrapage*analogRead(pinCCD);
  EnregistreDonnee(7, seuilBasRattrapageD);
  
  
  
  seuilHautDifferenceRattrapageG=hautGauche-(hautGauche-basGauche)/paramDiff;
  EnregistreDonnee(8, seuilHautDifferenceRattrapageG);
  
  seuilHautDifferenceRattrapageD=hautDroite-(hautDroite-basDroite)/paramDiff;
  EnregistreDonnee(9, seuilHautDifferenceRattrapageD);
  
  //On enregistre dans la mémoire eeprom, pour pouvoir tester sans avoir à re-qualibrer.
  //EEPROM.write(0,seuilHautRattrapeeG);
}

//On éteind les diodes qui doivent l'etre
//permet d'avoir des diodes allumées pendant des cycles entiers, pour qu'elles soient suffisament lumineuses.
void DiodesOff()
{
  if(cycleAllumeDiode1>1)
  {
    cycleAllumeDiode1--;
  }
  else
  {
    if(cycleAllumeDiode1==1)
    {
      digitalWrite(pinLed1,LOW);
      cycleAllumeDiode1--;
    }
  }
  if(cycleAllumeDiode2>0)
  {
    cycleAllumeDiode2--;
  }
  else
  {
    if(cycleAllumeDiode2==1)
    {
      digitalWrite(pinLed2,LOW);
      cycleAllumeDiode2--;
    }
  }
  if(cycleAllumeDiode3>0)
  {
    cycleAllumeDiode3--;
  }
  else
  {
    if(cycleAllumeDiode3==1)
    {
      digitalWrite(pinLed3,LOW);
      cycleAllumeDiode3--;
    }
  }
  
}

void DiodeOn(int numeroLed, int duree)
{
  if(numeroLed==pinLed1)
  {
    cycleAllumeDiode1=duree;
    digitalWrite(pinLed1,HIGH);
  }
  if(numeroLed==pinLed2)
  {
    cycleAllumeDiode2=duree;
    digitalWrite(pinLed2,HIGH);
  }
  if(numeroLed==pinLed3)
  {
    cycleAllumeDiode3=duree;
    digitalWrite(pinLed3,HIGH);
  }
}

void EnregistreDonnee(int adresse, int valeur)//Enregistre un nombre entre 0 et 1023 dans l'EEPROM
{
  if(valeur>=3*256)
  {
    EEPROM.write(adresse*4+3,valeur-3*256);//Reste bien compris entre 0 et 255
    EEPROM.write(adresse*4+2,255);
    EEPROM.write(adresse*4+1,255);
    EEPROM.write(adresse*4+0,255);
  }
  else
  {
    EEPROM.write(adresse*4+3,0);
    if(valeur>=2*256)
    {
      EEPROM.write(adresse*4+2,valeur-2*256);//Reste bien compris entre 0 et 255
      EEPROM.write(adresse*4+1,255);
      EEPROM.write(adresse*4+0,255);
    }
    else
    {
      EEPROM.write(adresse*4+2,0);
      if(valeur>=1*256)
      {
        EEPROM.write(adresse*4+1,valeur-1*256);//Reste bien compris entre 0 et 255
        EEPROM.write(adresse*4+0,255);
      }
      else
      {
        EEPROM.write(adresse*4+1,0);
        EEPROM.write(adresse*4+0,valeur-0*256);//Reste bien compris entre 0 et 255
      }
    }
  }
}

int LireDonnee(int adresse)//Lit un nombre entre 0 et 1023 dans l'EEPROM
{
  int valeur = 0;
  int lu = 0;
  valeur += EEPROM.read(adresse*4+0);
  
  lu=EEPROM.read(adresse*4+1);
  if(lu)
  {
    valeur+=lu+1;//EEPROM.read va de 0 à 255
    lu=EEPROM.read(adresse*4+2);
    if(lu)
    {
      valeur+=lu+1;//EEPROM.read va de 0 à 255
      lu=EEPROM.read(adresse*4+3);
      if(lu)
      {
        valeur+=lu+1;//EEPROM.read va de 0 à 255
      }
    }
  }
  return valeur;
}

