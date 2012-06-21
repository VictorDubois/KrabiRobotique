#ifndef SHARPSENSOR_H
#define SHARPSENSOR_H


#include <AnalogSensor.h>
#include "variable.h"
#ifndef ROBOTHW
    #include <QKeyEvent>
#endif

/** @brief Classe des gestions des capteurs sharps */
class SharpSensor : public AnalogSensor
{
    public:
        /** @brief Permet de nommer les différents capteurs */
        enum SharpName
        {
            /** @brief Aucun capteur */
            NONE,
            /** @brief Capteur arrière */
            BACK,
            /** @brief Capteur avant gauche */
            FRONT_LEFT,
            /** @brief Capteur avant droit */
            FRONT_RIGTH,
            /** @brief Capteur gauche */
            LEFT,
            /** @brief Capteur droit */
            RIGTH,
            /** @brief Capteur avant centrale */
            FRONT
        };
        /** @brief Permet de nommer les différents capteurs */
        typedef enum SharpName SharpName;

        /** @brief Constructeur d'un capteur sharp *
        *   @param name Identifient du capteur sharp pour la stratégie *
        *   @param channel Canal de l'ADC utilisé pour ce capteur. *
        *   @param pData Pointeur vers les données brutes du capteur directement sortie du ADC*/
        SharpSensor(SharpName name,uint8_t channel, uint16_t* pData);
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
        static uint16_t threshold;

        /** @brief Permet d'activer ce capteur sharp */
        void setActif();
        /** @brief Permet de désactiver ce capteur */
        void unsetActif();
        static bool estDesactive;

        #ifndef ROBOTHW
        void setEvent();
        #endif

    protected:
    private:
        /** @brief Compteur pour filtrer le signal numérique reçu. Ce compteur agit comme un filtre passe bas. */
        uint32_t counter;
        /** @brief Nom du capteur */
        SharpName name;
        /** @brief Valeur retourné par le capteur */
        bool output;
        /** @brief Indique si le capteur actuel est activé ou non. Si on il est à false, le capteur renvoie toujours false.*/
        bool actif;
        #ifndef ROBOTHW
        bool evt;
        #endif

};


#endif // SHARPSENSOR_H
