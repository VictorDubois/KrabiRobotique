#include "asservissement.h"
#include "strategieV2.h"
#include "bras.h"
//#include "ascenseur.h"

#include "misc.h"
//#include "capteurCouleur.h"

#define DBG_SIZE 400



//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];

float vitesseLin[DBG_SIZE];
float vitesseLinE[DBG_SIZE];
float linearDuty[DBG_SIZE];

float vitesseAng[DBG_SIZE];
float vitesseAngE[DBG_SIZE];
float angularDuty[DBG_SIZE];

//float posx[DBG_SIZE];
//float posy[DBG_SIZE];
//float angle[DBG_SIZE];
uint32_t dbgInc = 0;

Asservissement * Asservissement::asservissement = NULL; //Pour que nos variables static soient défini
bool Asservissement::matchFini = false;
const uint16_t Asservissement::nb_ms_between_updates = MS_BETWEEN_UPDATE;

Asservissement::Asservissement(Odometrie* _odometrie) :
    seuil_collision(SEUIL_COLISION),
    buffer_collision(0xffffffff)
{
    vitesseLineaire = 0;
    vitesseAngulaire = 0;
	odometrie = _odometrie;

    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;
    asserCount = 0;
#ifdef CAPTEURS
    sensors = Sensors::getSensors();
#endif

#ifdef ROBOTHW  //on définie les interruptions possibles dues à certains ports
    *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1
    *((uint32_t *)(STK_LOAD_ADDR)) = 2*9000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)

    NVIC_InitTypeDef SysTick_IRQ;

    SysTick_IRQ.NVIC_IRQChannel = SysTick_IRQn;
    SysTick_IRQ.NVIC_IRQChannelCmd = ENABLE;
    SysTick_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    SysTick_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&SysTick_IRQ);
#endif
}

void Asservissement::setLinearSpeed(Vitesse vitesse)
{
    vitesseLineaire = vitesse;
}

void Asservissement::setAngularSpeed(VitesseAngulaire vitesse)
{
    vitesseAngulaire = vitesse;
}

void Asservissement::setCommandSpeeds(Command* command)
{
    if (command == NULL)
    {
        setLinearSpeed(0);
        setAngularSpeed(0);
        return;
    }
    setLinearSpeed(command->getLinearSpeed());
    setAngularSpeed(command->getAngularSpeed());
}

Distance Asservissement::getLinearSpeed()
{
    return vitesseLineaire;
}

Angle Asservissement::getAngularSpeed()
{
    return vitesseAngulaire;
}

void Asservissement::update(void)
{
/*
#ifdef CAPTEURS
        AnalogSensor::startConversion(); // On lance la conversion des données que l'on reçois des capteurs pour les avoir au bon moment
#endif
*/
    asserCount++;
/*
#ifdef ROUES
    //On arrete le robot pour être sur que tout soit réinitialisé
    if(asserCount > CPT_BEFORE_RAZ)
    {
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
    }
#endif*/

    static int zer = 0;
    static bool tr = true;
    if ((zer % 100) == 0)
        tr = !tr;
#ifdef ROBOTHW
    if (tr)
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    else
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
#endif

    if (1/*asserCount< 85000/MS_BETWEEN_UPDATE && !Asservissement::matchFini*/)
    {

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();      //Variable juste pour avoir un code plus lisible par la suite
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();    //idem
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();   //idem

        StrategieV2::update();

#ifdef ROUES
/*
#ifdef CAPTEURS
    bool testcap = sensors->detectedSharp()->getSize() > 0;
#else

    bool testcap = false;
#endif*/

/*if (testcap)
{
    Command::freinageDUrgence(true);
  //  linearDutySent = 0;
  //  angularDutySent = 0;
}
else
    Command::freinageDUrgence(false);*/
#endif //ROUES

        //Puis on les récupéres
        float vitesse_lineaire_a_atteindre = getLinearSpeed();
        float vitesse_angulaire_a_atteindre = getAngularSpeed();

        // le buffer de collision se vide si l'accélération demandé est trop forte. Normalement la commande vérifie ça.
 /*       //Il faudrai qu'il passe de marche arriére à marche avant à toute vitesse pour avoir une collision ...
        buffer_collision <<= 1;
        buffer_collision |= fabs((vitesse_lineaire_atteinte - vitesse_lineaire_a_atteindre)) < seuil_collision && fabs((vitesse_angulaire_atteinte - vitesse_angulaire_a_atteindre)) < SEUIL_COLISION_ANG;
*/
#ifdef ROUES


        //on filtre l'erreur de vitesse lineaire et angulaire
        linearDutySent +=  pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-vitesse_lineaire_atteinte);
        angularDutySent += pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-vitesse_angulaire_atteinte);

        //Et on borne la somme de ces valeurs filtrée entre -> voir ci dessous
        linearDutySent =  MIN(MAX(linearDutySent, LINEARE_DUTY_MIN),LINEARE_DUTY_MAX);
        angularDutySent = MIN(MAX(angularDutySent, ANGULARE_DUTY_MIN),ANGULARE_DUTY_MAX);

        //On évite que le robot fasse du bruit quand il est à l'arrêt
 //       linearDutySent = fabs(linearDutySent) > 0.05 || vitesse_lineaire_a_atteindre > 0.01 ? linearDutySent : 0;
 //       angularDutySent = fabs(angularDutySent) > 0.05 || vitesse_angulaire_a_atteindre > 0.0001 ? angularDutySent : 0;


// Pour afficher les courbes :
            if(dbgInc<DBG_SIZE)
            {

                  vitesseLin[dbgInc] = vitesse_lineaire_atteinte;
                   vitesseLinE[dbgInc] = vitesse_lineaire_a_atteindre;
                  linearDuty[dbgInc] = linearDutySent;

                   vitesseAng[dbgInc] = vitesse_angulaire_atteinte;
                   vitesseAngE[dbgInc] = vitesse_angulaire_a_atteindre;
                   angularDuty[dbgInc] = angularDutySent;

                  dbgInc++;

            }
            else
            {

          //     roues.gauche.tourne(0.0);
        //   roues.droite.tourne(0.0);
      //      dbgInc++;
            }


        if (0/*buffer_collision == 0x0 */)//|| GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_RESET) //Actif si le buffer_de colision est vide.
        {   //Si on détecte quelque chose, on s'arréte

            roues.gauche.tourne(0.);
            roues.droite.tourne(0.);
        }
        else
        {   //Sinon les roues tourne de façon borné et le fais d'avoir filtrées les valeurs permet de compenser les erreurs passées et de faire tournées chaque roues de façon
            // à tourner et avancer correctement
            roues.gauche.tourne(MIN(MAX(+linearDutySent-angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
            roues.droite.tourne(MIN(MAX(+linearDutySent+angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
        }
    }
    else
    {
        roues.gauche.tourne(0.);
        roues.droite.tourne(0.);
    }
#else
}
#endif
}

#ifdef ROBOTHW
//pour lancer l'update à chaque tic d'horloge
extern "C" void SysTick_Handler()
{
/*
   static Roue* ascensseur = NULL;
   if (ascensseur==NULL)
        ascensseur = new Roue(TIM5, 4, GPIOA, GPIO_Pin_3, GPIOD, GPIO_Pin_4);
        ascensseur->tourne(0.6f);
*/
    Odometrie::odometrie->update();

#ifdef CAPTEURS
    Sensors* sensors = Sensors::getSensors();
    if (sensors != NULL)
        sensors->update();
#endif

    Asservissement::asservissement->update();

//    Ascenseur* ascenseur = Ascenseur::get();
//    if (ascenseur != NULL)
//        ascenseur->update();

/*
if (Odometrie::odometrie->ang < 0.2*3.1415/180.0 && Odometrie::odometrie->ang > -0.2*3.1415/180.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    }
*/
/*
   Odometrie::odometrie->update();
   if (Odometrie::odometrie->posX > -5000.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
    }
    else if (Odometrie::odometrie->posX < -5000.0)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);
    }
    else
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);
    }
*/

/*
    static CapteurCouleur* c = NULL;
    static int seuilMax = 200;
    static int seuilMin = 120;

    if (c == NULL)
        c = new CapteurCouleur(TIM2, GPIOA, GPIO_Pin_6);

    static uint16_t ticks[DBG_SIZE];
    static int nbBoucles = 0;

    if (nbBoucles % 200 == 100)
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
    if (nbBoucles % 200 == 199)
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);*/
/*
    uint16_t nbTicks = c->getTickValue();

    if (nbTicks > seuilMax)
        xallumerLED2();
    else
        xeteindreLED2();

    if (nbTicks < seuilMin)
        xallumerLED();
    else
        xeteindreLED();*/
/*
    if (nbBoucles < DBG_SIZE)
    {

        ticks[nbBoucles] = c->getTickValue();
        nbBoucles++;
    }
    else
    {
        nbBoucles++;
    }
*/
}

#endif

void Asservissement::finMatch()
{
    Asservissement::matchFini = true;
    #ifdef ROBOTHW
    Bras::getBras()->arretUrgence();
    Bras::getBras()->monterRateau();
    #endif
}
