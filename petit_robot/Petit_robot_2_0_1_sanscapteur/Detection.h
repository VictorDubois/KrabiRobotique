#ifndef DEF_DETECTION // Si la constante n'a pas été définie` le fichier n'a jamais été inclus
#define DEF_DETECTION // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus

#include "Sharp.h"
#include "Ultrason.h"

#define NOMBRECAPTEUR 5


class Detection
{
    public:
 
  Detection();
  ~Detection();
  int JePeuxAvancer(int sensVoulu);
  void LireCapteursDistance();
 
    private:
   
   
  int capteurVoitQQch[NOMBRECAPTEUR];
  int capteurVoitObstacle[NOMBRECAPTEUR];//tableau permettant de pallier le problème du bruit : il faut capter 8 fois d'affillée pour voir un obstacle
  //Ultrason ping;
  /*Sharp *capteurAvantG;
  Sharp *capteurAvantD;
  Sharp *capteurMilieu;
  Sharp *capteurHaut;
  Sharp *capteurArriere;*/
  Sharp **capteurSharp;


};

#endif

