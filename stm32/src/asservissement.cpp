#include "asservissement.h"

Asservissement * Asservissement::asservissement = NULL; //Pour que nos variables static soient défini
const uint16_t Asservissement::nb_ms_between_updates = MS_BETWEEN_UPDATE;

Asservissement::Asservissement(Odometrie* _odometrie) :
    seuil_collision(SEUIL_COLISION),
    buffer_collision(0xffffffff)
{
	odometrie = _odometrie;
	command = NULL;
    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;
    asserCount = 0;

#ifdef ROBOTHW  //on définie les intéruptions possible du à certains port
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
    asserCount++;

#ifdef ROUES
    //On arrete le robot pour être sur que tout soit réinitialisé
    if(asserCount > CPT_BEFORE_RAZ)
    {
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
    }
#endif

#ifdef CAPTEURS
        capteurs.startConversion(); //On lance la conversion des données que l'on reçois des capteurs pour les avoir au bon moment
#endif
        odometrie->update();        //Enregistre la position actuelle du robot

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();      //Variable juste pour avoir un code plus lisible par la suite
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();    //idem
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();   //idem

        if(command) //si une commande est rentrée, on calcul les vitesse linéraire et de rotation à atteindre
            command->update(positionPlusAngleActuelle, vitesse_angulaire_atteinte, vitesse_lineaire_atteinte);

        //Puis on les récupéres
        float vitesse_lineaire_a_atteindre = getLinearSpeed();
        float vitesse_angulaire_a_atteindre = getAngularSpeed();

        // le buffer de collision se vide si l'accélération demandé est trop forte. Normalement la commande vérifie ça.
        //Il faudrai qu'il passe de marche arriére à marche avant à toute vitesse pour avoir une collision ...
        buffer_collision <<= 1;
        buffer_collision |= fabs((vitesse_lineaire_atteinte - vitesse_lineaire_a_atteindre)) < seuil_collision;

#ifdef ROUES
        //on filtre l'erreur de vitesse lineaire et angulaire
        linearDutySent += pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-vitesse_lineaire_atteinte);
        angularDutySent += pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-vitesse_angulaire_atteinte);

        //Et on borne la somme de ces valeurs filtrée entre -> voir ci dessous
        linearDutySent = MIN(MAX(linearDutySent, LINEARE_DUTY_MIN),LINEARE_DUTY_MAX);
        angularDutySent = MIN(MAX(angularDutySent, ANGULARE_DUTY_MIN),ANGULARE_DUTY_MAX);

#ifdef CAPTEURS
    bool testcap = capteurs.getValue(Capteurs::AvantDroitExt) || capteurs.getValue(Capteurs::AvantDroitInt) || capteurs.getValue(Capteurs::AvantGaucheExt) || capteurs.getValue(Capteurs::AvantGaucheInt) || capteurs.getValue(Capteurs::Derriere);
#else
    bool testcap = false;
#endif

    if (testcap)
    {   //Si on détecte quelque chose, on s'arréte
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
        roues.gauche.tourne(0.);
        roues.droite.tourne(0.);
    }
    else
    {   //Sinon les roues tourne de façon borné et le fais d'avoir filtrées les valeurs permet de compenser les erreurs passées et de faire tournées chaque roues de façon
        // à tourner et avancer correctement
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
        roues.gauche.tourne(MIN(MAX(-linearDutySent+angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
        roues.droite.tourne(MIN(MAX(-linearDutySent-angularDutySent, LINEARE_DUTY_MIN+ANGULARE_DUTY_MIN),LINEARE_DUTY_MAX+ANGULARE_DUTY_MAX));
    }
#endif
}

//pour lancer l'update à chaque tic d'horloge
extern "C" void SysTick_Handler()
{
    Asservissement::asservissement->update();
}
