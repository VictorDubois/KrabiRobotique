#include "Diode.h"
#include "Arduino.h"

//using namespace std;

Diode::Diode(int diodePin)//Constructeur
{
  int duree = 0;
  diodePin = diodePin;
}

Diode::~Diode()//Destructeur
{

}

//On éteind les diodes qui doivent l'etre
//permet d'avoir des diodes allumées pendant des cycles entiers, pour qu'elles soient suffisament lumineuses.
void Diode::DiodeOff()
{
  
  if(dureeEncoreAllumee>1)
  {
    dureeEncoreAllumee--;
  }
  else
  {
    if(dureeEncoreAllumee==1)
    {
      digitalWrite(diodePin,LOW);
      dureeEncoreAllumee--;
    }
  }
}

void Diode::DiodeOn(int duree)
{
  dureeEncoreAllumee=duree;
  digitalWrite(diodePin,HIGH);
}

