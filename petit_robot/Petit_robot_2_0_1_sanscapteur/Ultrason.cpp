#include "Ultrason.h"
#include "Arduino.h"
#include "Capteur.h"

#define DELAI_ATTENTE_MAX 10000//On max, on attent 10ms que le son revienne.
#define DISTANCE_MAX_DETECTION 25//S'il y a qqch à moins de 25cm, on s'arrete.
#define DIST_MIN_DETECTION 1//si le capteur renvoit 0, c'est soit que l'objet est très loin, soit qu'il y a un pb.

Ultrason::Ultrason() : Capteur(0)//Je ne vois pas trop comment faire sans mettre un constructeur bidon...
{
  
}


Ultrason::Ultrason(int capteurPin) : Capteur(capteurPin)
{
  
}

int Ultrason::VoitQQch()
{
  Update();
  if(distance < DISTANCE_MAX_DETECTION)
  {
    return 1;
  }
  else
  {
    return 0;
  }  
}

//int Ultrason::Distance()//Renvoit la distance du plus proche objet du capteur
void Ultrason::Update()
{

      
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(capteurPin, OUTPUT);
  digitalWrite(capteurPin, LOW);
  delayMicroseconds(2);
  digitalWrite(capteurPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(capteurPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(capteurPin, INPUT);
  duration = pulseIn(capteurPin, HIGH,10000);//On n'attend pas plus de 10 millisecondes le signal de retour.

  // convert the time into a distance
  cm = duration / 29 / 2;
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  if(cm<DIST_MIN_DETECTION)//si le signal n'est pas revenu à temps, il retourne 0. mais en fait l'objet est à au moins 50 cm.
  {
    cm=50;
  }
  
  distance = cm;
}

