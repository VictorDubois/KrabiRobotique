#include "asservissement.h"
#include "strategie.h"
#include "bras.h"

#include "misc.h"

#define DBG_SIZE 600

//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];

float vitesseLin[DBG_SIZE];
float vitesseLinE[DBG_SIZE];
//float linearDuty[DBG_SIZE];

float vitesseAng[DBG_SIZE];
float vitesseAngE[DBG_SIZE];
//float angularDuty[DBG_SIZE];

//float posx[DBG_SIZE];
//float posy[DBG_SIZE];
//float angle[DBG_SIZE];
uint32_t dbgInc = 0;

Asservissement * Asservissement::asservissement = NULL; //Pour que nos variables static soient défini
bool Asservissement::matchFini = false;
const uint16_t Asservissement::nb_ms_between_updates = MS_BETWEEN_UPDATE;
int toto = 0;
int caca = 0;


Asservissement::Asservissement(Odometrie* _odometrie) :
    seuil_collision(SEUIL_COLISION),
    buffer_collision(0xffffffff)
{

	odometrie = _odometrie;
//	if (odometrie == NULL)
//        xallumerLED();

	command = NULL;
    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;
    asserCount = 0;
#ifdef CAPTEURS
    sensors = Sensors::getSensors();
#endif

#ifdef ROBOTHW  //on définie les interruptions possibles dues à certains ports
    *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1
    *((uint32_t *)(STK_LOAD_ADDR)) = 9000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)

    NVIC_InitTypeDef SysTick_IRQ;

    SysTick_IRQ.NVIC_IRQChannel = SysTick_IRQn;
    SysTick_IRQ.NVIC_IRQChannelCmd = ENABLE;
    SysTick_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    SysTick_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&SysTick_IRQ);
#endif
}

Distance Asservissement::getLinearSpeed()
{
    return command ? command->getLinearSpeed() : 0;
}

Angle Asservissement::getAngularSpeed()
{
    return command ? command->getAngularSpeed() : 0;
}

void Asservissement::update(void)
{




#ifdef CAPTEURS
        AnalogSensor::startConversion(); // On lance la conversion des données que l'on reçois des capteurs pour les avoir au bon moment
#endif

    asserCount++;

#ifdef ROUES
    //On arrete le robot pour être sur que tout soit réinitialisé
    if(asserCount > CPT_BEFORE_RAZ)
    {
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
    }
#endif



    if (asserCount< 85000/MS_BETWEEN_UPDATE && !Asservissement::matchFini)
    {

        odometrie->update();        //Enregistre la position actuelle du robot


        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();      //Variable juste pour avoir un code plus lisible par la suite
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();    //idem
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();   //idem


    /*    static int truc = 0;
truc++;
if ((truc/100)%2 == 0)
{

        #ifdef STM32F10X_CL
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); //ON
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET); //OFF
        #endif

}
else
{
        #ifdef STM32F10X_CL
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); //OFF
         GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); //ON
        #endif
}
        */


#ifdef CAPTEURS
        sensors->update();
#endif


        Strategie::getInstance()->update();

        if (command != NULL) //si une commande est rentrée, on calcul les vitesse linéraire et de rotation à atteindre
        {
            command->update();
        }

#ifdef ROUES

#ifdef CAPTEURS
    bool testcap = sensors->detectedSharp()->getSize() > 0;
#else

    bool testcap = false;
#endif

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
        float vitesse_lineaire_a_atteindre = /*0;//*/getLinearSpeed();
        float vitesse_angulaire_a_atteindre =  /*VITESSE_ANGULAIRE_MAX; //*/getAngularSpeed();

        // le buffer de collision se vide si l'accélération demandé est trop forte. Normalement la commande vérifie ça.
        //Il faudrai qu'il passe de marche arriére à marche avant à toute vitesse pour avoir une collision ...
        buffer_collision <<= 1;
        buffer_collision |= fabs((vitesse_lineaire_atteinte - vitesse_lineaire_a_atteindre)) < seuil_collision && fabs((vitesse_angulaire_atteinte - vitesse_angulaire_a_atteindre)) < SEUIL_COLISION_ANG;

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
            if(toto < 1 && dbgInc<DBG_SIZE)
            {

        //roueGauche[caca] = odometrie->roueCodeuseGauche->getTickValue();
        //roueDroite[caca] = odometrie->roueCodeuseDroite->getTickValue();
                   vitesseLin[dbgInc] = vitesse_lineaire_atteinte;
                   vitesseLinE[dbgInc] = vitesse_lineaire_a_atteindre;
//                  linearDuty[dbgInc] = linearDutySent;

                   vitesseAng[dbgInc] = vitesse_angulaire_atteinte;
                   vitesseAngE[dbgInc] = vitesse_angulaire_a_atteindre;
//                   angularDuty[dbgInc] = angularDutySent;

//                  posx[caca] = positionPlusAngleActuelle.position.x;
//                   posy[caca] = positionPlusAngleActuelle.position.y;
//                   angle[caca] = positionPlusAngleActuelle.angle; //*angle_restant.getValueInRadian();*///distance_restante; //positionPlusAngleActuelle.angle.getValueInRadian()*180/M_PI;
                   dbgInc++;
                   caca++;
            }
           toto = (toto+1) % 3;




        if (buffer_collision == 0x0 )//|| GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)  == Bit_RESET) //Actif si le buffer_de colision est vide.
        {   //Si on détecte quelque chose, on s'arréte

            roues.gauche.tourne(0.);
            roues.droite.tourne(0.);
        }
        else
        {   //Sinon les roues tourne de façon borné et le fais d'avoir filtrées les valeurs permet de compenser les erreurs passées et de faire tournées chaque roues de façon
            // à tourner et avancer correctement
            roues.gauche.tourne(MIN(MAX(-linearDutySent-angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
            roues.droite.tourne(MIN(MAX(-linearDutySent+angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
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
    Asservissement::asservissement->update();

}

#endif

void Asservissement::setCommand(Command* command)
{
    Asservissement::asservissement->command = command;
}

Command* Asservissement::getCommand()
{
    return (Asservissement::asservissement->command);
}


void Asservissement::finMatch()
{
    Asservissement::matchFini = true;
    #ifdef ROBOTHW
    Bras::getBras()->arretUrgence();
    Bras::getBras()->monterRateau();
    #endif
}
