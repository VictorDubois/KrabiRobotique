#ifndef DEF_CAPTEUR // Si la constante n'a pas été définie` le fichier n'a jamais été inclus
#define DEF_CAPTEUR // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus



class Capteur
{
    public:
 
  Capteur(int capteurPin);
   Capteur(int capteurPin, int valeur);
  ~Capteur();
  int GetValue();
  void Update();
 
    private:
    
    protected://Les capteurs sharp peuvent modifier leurs "valeur".
  
  int valeur; //Distance ou autre, la valeur renvoyée par le capteur.
  int capteurPin;
};

#endif
