#ifndef DEF_DIODE // Si la constante n'a pas été définie` le fichier n'a jamais été inclus
#define DEF_DIODE // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus


class Diode
{
    public:
 
  Diode(int diodePin);
  ~Diode();
  void DiodeOff();//eteind une diode
  void DiodeOn(int duree);//allume une diode
 
    private:
 
  int dureeEncoreAllumee;//Correspond au nombre de cycles pendant lesquels la diode va continuer à etre allumée.
  int diodePin;//le pin de l'arduino auquel est attché la diode.

};

#endif

