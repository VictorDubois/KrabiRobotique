#ifndef SHARPSENSOR_H
#define SHARPSENSOR_H

#include "analogSensor.h"
#include "constantes.h"

#ifndef ROBOTHW
    //#include <QKeyEvent>
#endif

/** @brief Classe des gestions des capteurs sharps */
class SharpSensor : public AnalogSensor
{
    public:
        /** @brief Permet de nommer les différents capteurs */
        enum SharpName
        {
            #if defined(STM32F10X_MD) || defined(STM32F40_41xxx) // Pin pour le stm32 h103
                BACK_RIGHT,
                BACK_LEFT,
                BACK_MIDDLE,
                FRONT_RIGHT,
                FRONT_LEFT,
                FRONT_MIDDLE,
                END_SHARP_NAME,
                NONE = 7
            #else // Pin pour le stm32 h107 et le simu

                BACK_RIGHT_SIDE,
                BACK_RIGHT,
                BACK_LEFT,
                BACK_LEFT_SIDE,
                FRONT_LEFT_SIDE,
                FRONT_LEFT,
                FRONT_RIGHT,
                FRONT_RIGHT_SIDE,
                END_SHARP_NAME,
                NONE = 8
//
//                NONE = 8,
//                BACK_RIGHT = 6,
//                BACK_LEFT = 4,
//                FRONT_LEFT = 0,
//                FRONT_RIGHT = 1,
//                LEFT_FRONT = 2,
//                LEFT_BACK = 5,
//                RIGHT_FRONT = 3,
//                RIGHT_BACK = 7,
//                END_SHARP_NAME = 8
                /*
                NONE = 6,
                BACK_RIGHT = 4,
                BACK_LEFT = 9,
                BACK_MIDDLE = 5,
                FRONT_SIDE_LEFT = 2,
                FRONT_SIDE_RIGHT = 3,
                FRONT_LEFT = 0,
                FRONT_RIGHT = 1,
                ELEVATOR_DOWN = 8,
                ELEVATOR_TOP = 7,
                END_SHARP_NAME = 10
                */
            #endif

        };

        /** @brief Constructeur d'un capteur sharp *
        *   @param name Identifient du capteur sharp pour la stratégie *
        *   @param channel Canal de l'ADC utilisé pour ce capteur. *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie du ADC*/
        SharpSensor(SharpName name,uint8_t channel, DMA_MEMORY_TYPE* pData, int seuil = SEUIL_DETECTION);

        /** @brief Destructeur de cette classe */
        virtual ~SharpSensor();

        /** @brief Permet de récupérer les données rendu diponible par le capteur sharp*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur. Cette structure sera de type SHARP et la seul donnée utile sera donc la variable b qui sera a true si un obstacle est devant le capteur sharp, false sinon. */
        OutputSensor getValue();

        /** @brief Accesseur de name */
        SharpName getName();

        /** @brief Met à jour la valeur de retour du capteur en étudiant la sortie analogique. *
        *   @warning Il faut appeler cette fonction souvent pour que la value du retour du capteur soit la plus juste possible. */
        void updateValue();

        /** @brief Seuil de détection utilisé pour les calibrer les capteurs sharp. Un retour supérieur à ce seuil sera considéré comme la détection d'un obstacle */
        static int threshold;

        /** @brief Permet d'activer ce capteur sharp */
        void setActif();

        /** @brief Permet de désactiver ce capteur */
        void unsetActif();

        static bool estDesactive;

        #ifndef ROBOTHW
        void setEvent();
        void unsetEvent();
        #endif

    private:

        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint8_t counter;

        /** @brief Nom du capteur */
        SharpName name;

        /** @brief Valeur retourné par le capteur */
        bool output;

        /** @brief Indique si le capteur actuel est activé ou non. Si on il est à false, le capteur renvoie toujours false.*/
        bool actif;

        int value;

        #ifndef ROBOTHW
        bool evt;
        #endif

        DMA_MEMORY_TYPE seuilDetection;
};


#endif // SHARPSENSOR_H
