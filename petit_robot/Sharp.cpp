#include "Sharp.h"
#include "Arduino.h"


Sharp::Sharp(): Capteur(0)
{
  this->seuilDetection=200;
}

Sharp::Sharp(int capteurPin, int seuil) : Capteur(capteurPin, valeur), seuilDetection(seuil)
{
  //this->seuilDetection=200;
  //valeur=0;
  
}

void Sharp::Update()
{
  valeur = analogRead(capteurPin);
  //Serial.println( capteurPin);
   //Serial.println( analogRead(capteurPin));
  //valeur=0;
}

int Sharp::VoitQQch()
{
  Update();
  //if(valeur>seuilDetection)
 
  if(valeur>seuilDetection)
  {
    
    //delay(100);
    return 1;
  }
  else
  {
    //Serial.println(0);
    return 0;
  }
}
