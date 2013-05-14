#ifndef CAPTEURCOULEUR_H
#define CAPTEURCOULEUR_H

#ifdef ROBOTHW
#include "stm32f10x_tim.h"
#include "command.h"

enum PositionCapteurCouleur
{
    GAUCHE_HAUT,
    GAUCHE_BAS,
    DROITE_HAUT,
    DROITE_BAS
};

enum FiltreCapteurCouleur
{
    FILTRE_ROUGE,
    FILTRE_VERT,
    FILTRE_BLEU,
    FILTRE_BLANC
};

/// @brief Classe permettant de connaitre le nombre de ticks des capteurs couleur
/// Le capteur renvoit un signal en créneaux dont la fréquence dépend de la luminosité
/// Il se branche sur le channel 1 d'un timer
class CapteurCouleur
{
    private:

        /// @brief Le Timer utilisé
        TIM_TypeDef* m_TIMx;

        // pin des diodes
        GPIO_TypeDef* m_GPIO_diodesRouges;
        uint16_t m_GPIO_Pin_diodesRouges;
        GPIO_TypeDef* m_GPIO_diodesBleues;
        uint16_t m_GPIO_Pin_diodesBleues;

        // pins de selection
        GPIO_TypeDef* m_GPIO_selectCapteur1;
        uint16_t m_GPIO_Pin_selectCapteur1;
        GPIO_TypeDef* m_GPIO_selectCapteur2;
        uint16_t m_GPIO_Pin_selectCapteur2;

        // pins de filtres
        GPIO_TypeDef* m_GPIO_selectFiltre1;
        uint16_t m_GPIO_Pin_selectFiltre1;
        GPIO_TypeDef* m_GPIO_selectFiltre2;
        uint16_t m_GPIO_Pin_selectFiltre2;

    public:

        /// @brief Constructeur en spécifiant le timer et la pin
        /// Le channel 1 du timer doit etre utiliseé
        /// On donne aussi les pins des diodes rouges, bleues et les 2 pins de selection du capteur
        CapteurCouleur(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_timer, uint16_t GPIO_Pin_timer,
                       GPIO_TypeDef* GPIO_diodesRouges, uint16_t GPIO_Pin_diodesRouges,
                       GPIO_TypeDef* GPIO_diodesBleues, uint16_t GPIO_Pin_diodesBleues,
                       GPIO_TypeDef* GPIO_selectCapteur1, uint16_t GPIO_Pin_selectCapteur1,
                       GPIO_TypeDef* GPIO_selectCapteur2, uint16_t GPIO_Pin_selectCapteur2,
                       GPIO_TypeDef* GPIO_selectFiltre1, uint16_t GPIO_Pin_selectFiltre1,
                       GPIO_TypeDef* GPIO_selectFiltre2, uint16_t GPIO_Pin_selectFiltre2);

        // allume/éteint les diodes
        void allumerDiodesRouges(bool allumer);
        void allumerDiodesBleues(bool allumer);

        // selectionne un filtre
        void selectionnerFiltre(FiltreCapteurCouleur filtre);

        // selectionne le capteur
        void activerCapteur(PositionCapteurCouleur position);

        // Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
        // ou depuis le dernier appel de la selection du capteur
        uint16_t getTickValue();
};

class CommandCalibrerCapteurCouleur : public Command
{
    public:

        // permet de calibrer le capteur couleur en calculant la valeur moyenne de chaque capteur
        // nécessite 5 updates chaque 5 ms
        // la première update peut se faire juste après la construction
        CommandCalibrerCapteurCouleur(CapteurCouleur* capteur);

        // récupère la valeur d'un capteur et passe à un autre
        virtual void update();

        // renvoient 0
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // renvoit si le capteur a fini sa calibration
        // le résultat est lisible dans getTicksMoyens()
        virtual bool fini() const;

        // une fois fini, renvoit le seuil calculé
        uint16_t getTicksMoyens() const;

    protected:

        CapteurCouleur* capteurCouleur;
        int state;

        uint16_t resultat;
};

class CommandCheckCouleur : public Command
{
    public:

        // nombres d'updates pour allumer/eteindre completement une led
        static const int nbUpdatePourAllumerLed = 10;

        // check la couleur d'un capteur
        CommandCheckCouleur(CapteurCouleur* capteur, PositionCapteurCouleur pos, uint16_t seuil);

        // check la couleur
        virtual void update();

        // renvoient 0
        virtual Vitesse getLinearSpeed();
        virtual Angle getAngularSpeed();

        // renvoit si le capteur a fini de check la couleur
        // le résultat est disponible dans les fonctions bleue() et rouge()
        virtual bool fini() const;

        // une fois fini, renvoit la couleur
        // les 2 peuvent renvoyer true si on est pas sur de la couleur
        bool bleue() const;
        bool rouge() const;

    protected:

        uint16_t seuilMoyenne;
        CapteurCouleur* capteurCouleur;
        uint16_t bleuMesure;
        uint16_t rougeMesure;
        int nbUpdatesRestantes;
        int state;
};


#endif // ROBOTHW

#endif // QUADRATURECODERHANDLER_H
