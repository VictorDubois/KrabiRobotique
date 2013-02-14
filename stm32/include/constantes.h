#ifndef CONSTANTES_H
#define CONSTANTES_H

// macros communes
#define MIN(a,b) ((a)>(b)?(b):(a))
#define MAX(a,b) ((a)<(b)?(b):(a))
#define DEGTORAD(a) (a/360*2*M_PI)
#define ANGLETOPULSE(a) (a*500)/124+1500

#ifndef NULL
#define NULL 0
#endif

//#define ROBOTHW
//#define CAPTEURS déjà mis dans asservissement

// HCTL_HANDLER
#define HCTL_BCL 1875000

// MOTEUR
#define NUM_TIMER_MOTEUR 4
#define PERIOD_TIMER_MOTEUR 71
#define PRESCALER_TIMER_MOTEUR 11000//11000//22000
#define CLOCK_TIMER_MOTEUR Timer::Div1

// TRAPEZOIDALCOMMAND
#define DISTANCE_ARRET 100 // 15
#define ANGLE_ARRET 0.08 //0.08

// Asservissement

#define SEUIL_COLISION 1
#define SEUIL_COLISION_ANG 0.002
#define MS_BETWEEN_UPDATE 10
#define CPT_BEFORE_RAZ 8500
#define LINEARE_DUTY_MAX 1.00
#define LINEARE_DUTY_MIN -1.00
#define ANGULARE_DUTY_MAX 0.80
#define ANGULARE_DUTY_MIN -0.80

// Capteurs

    /// @brief SEUIL_DETECTION Seuil de detection des capteurs sharp. Au dessus de cette valeur, un objet sera considéré comme présent devant le capteur.
#define SEUIL_DETECTION 2100. // 2000.
    /// @brief COEFFICIENT_LIN_ULTRASON Coefficient multiplicateur utilisé pour transformé la valeur analogique rendu par le capteur ultrason en une distance en metres.
#define COEFFICIENT_LIN_ULTRASON 2.54/2.*1.674003419
    /// @brief NB_CAPTEUR_A_ADC Nombre de capteur nécéssitant d'utiliser un ADC
#define NB_CAPTEUR_A_ADC 6

// Servomoteurs

    /// @brief BALAI_G_CLOSED Angle du servomoteur pour lequel le balai gauche est fermé.
#define BALAI_D_CLOSED 110
    /// @brief BALAI_D_CLOSED Angle du servomoteur pour lequel le balai droit est fermé.
#define BALAI_G_CLOSED -150
    /// @brief BALAI_G_OPEN Angle du servomoteur pour lequel le balai gauche est ouvert.
#define BALAI_D_OPEN -150
    /// @brief BALAI_D_OPEN Angle du servomoteur pour lequel le balai droit est ouvert.
#define BALAI_G_OPEN 110
    /// @brief RATEAU_HAUT Angle du servomoteur pour lequel le rateau est en haut.
#define RATEAU_HAUT -270
    /// @brief RATEAU_BAS Angle du servomoteur pour lequel le rateau est en haut.
#define RATEAU_BAS -180//-200

// Command

#define VITESSE_LINEAIRE_MAX 4
#define VITESSE_ANGULAIRE_MAX  0.009//0.008//0.005
#define ACCELERATION_LINEAIRE_MAX  0.15//0.1//0.05
#define ACCELERATION_ANGULAIRE_MAX (2*M_PI/5000.0)//(2*M_PI/5000.0)//(2*M_PI/20000.0) //(2*M_PI/5000.0)

// Odometrie

#define TAILLE_ENTRAXE 265
#define RAYON_ROUE  40.326*1.283614189 // 40.326
#define NBR_TICK_PAR_TOUR 8192
#define COEFF_AJOUST_ANGLE 0.986608174

// PIDFILTERANGLE
#define FILTER_ANGLE_KP 3//3.6 //0.1
#define FILTER_ANGLE_KI 0.08//0.01//0.1
#define FILTER_ANGLE_KD 40//35 //30 //35//0.001//35
#define FILTER_ANGLE_COEF 1//0.83

// PIDFILTERLINEAIRE
#define FILTER_LINEAIRE_KP 0.015//0.02 // 0.1
#define FILTER_LINEAIRE_KI 0.0002//0.21//0.22//0.02//0.02
#define FILTER_LINEAIRE_KD 0.3//0.3//0.01//11.25//5//0.3//0.3
#define FILTER_LINEAIRE_COEF 1//0.83

// ROUE
#define RAPPORT_OK 0.05//0.05
#define RAPPORT_SUPPLEMENTAIRE 0.08

// SERVO
/// @brief NUMERO_TIMER_SERVO Numéro du Timer (TIM) sur lequel sont les servos
#define NUMERO_TIMER_SERVO 3
/// @brief PERIOD_TIMER_SERVO Période du timer.
#define PERIOD_TIMER_SERVO 20000
/// @brief PRESCALER_TIMER_SERVO Facteur de division de l’horloge : @f$ fr\acute{e}quence du timer = \frac{72 MHz}{ timClockDivision (timPrescaler + 1)} @f$ .
#define PRESCALER_TIMER_SERVO 71
/// @brief CLOCK_TIMER_SERVO : division d’horloge supplémentaire, voire Timer::ClkDivision.
#define CLOCK_TIMER_SERVO Timer::Div1
#define FREQUENCE_SERVO 1e6

// STRATEGIE
#define INSTRUCTION_COLLISION 128
#define POS_DEPART_X 260
#define POS_DEPART_Y 250
#define RAYON_ROBOT 250
#define ANGLE_DEPART 0
// COMMAND_GO_TO
#define PATH_LENGTH 800

#endif // CONSTANTES_H