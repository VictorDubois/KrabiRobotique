#ifndef CALIBRATION_H
#define CALIBRATION_H

/** @brief Classe "static" permettant de calibrer les coordonnées du robot sur la table */
class Calibration
{
    public:
        /** @brief Permet de calibrer le zero des X. Ça suppose que le cul du robot est orienté vers le "bas" de la table. */
        static void calibrerZeroX();
        /** @brief Permet de calibrer le maximum des X. Ça suppose que le cul du robot est orienté vers le "haut" de la table. */
        static void calibrerMaxX();
        /** @brief Permet de calibrer le maximum des Y. Ça suppose que le cul du robot est orienté vers le coté "0 Y" de la table. */
        static void calibrerZeroY();
        /** @brief Permet de calibrer le maximum des Y. Ça suppose que le cul du robot est orienté vers le coté "Max Y" de la table. */
        static void calibrerMaxY();
        /** @brief Permet de calibrer le robot au début de partie. Ça suppose que le cul du robot est orienté vers le "bas" de la table. */
        static void calibrationInitial();
    protected:
    private:
};

#endif // CALIBRATION_H
