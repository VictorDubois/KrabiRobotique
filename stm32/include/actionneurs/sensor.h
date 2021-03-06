#ifndef SENSOR_H
#define SENSOR_H

/// @brief Classe abstraite de gestion des capteurs
class Sensor
{
    public:

        /// @brief Enumération permettant de définir de quel type de capteur les données sont issues
        enum SensorType
        {
            /// Pour les capteurs sharp. Valeur attendue : un booléen valant true si le seuil de détection est dépassé (objet devant).
            SHARP,

            /// Pour les capteurs ultra son. Valeur attendue : un entier représentant la distance en mm de l'objet le plus proche observé.
            ULTRASOUND,

            /// Pour les capteurs fin de course. Valeur attendue : un booléen valant true si le capteur est enfoncé.
            LIMIT_SWITCH,

            /// Pour les barrières optiques. Valeur attendue : un booléen valant true si un objet coupe la barrière optique.
            LIGTH_BARRIER
        };

        /// @brief Structure permettant de stocker les valeurs les données retournées par le capteur
        typedef struct OutputSensor
        {
            /// @brief Permet de savoir de quel type de capteur les données sont issu.
            SensorType type;

            /// @brief Permet de stocker la valeur numérique de retour des capteurs de type ULTRASOUND. Cette valeur correspond à une distance en mm
            float f;

            /// @brief Permet de stocker la valeur booléen de retour d'un capteur de type SHARP, LIMIT_SWITCH ou LIGTH_BARRIER
            bool b;
        } OutputSensor;

        /// @brief Constructeur d'un capteur de base
        Sensor();

        /// @brief Destructeur de la classe
        virtual ~Sensor();

        /** @brief Permet de récupérer les données rendues diponibles par le capteur*
        *   @return Retourne une structure OutputSensor contenant les données traitées du capteur */
        virtual OutputSensor getValue() = 0;
};

#endif // SENSOR_H
