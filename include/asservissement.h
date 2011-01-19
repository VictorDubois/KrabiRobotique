#ifndef ASSERVISSEMENT_H_INCLUDED
#define ASSERVISSEMENT_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "distance.h"
#include "Angle.h"
#include "pid_filter_distance.h"
#include "pid_filter_angle.h"
#ifdef ROBOTHW
#include "roues.h"
#include "capteurs.h"
#endif
#include <stdint.h>

class Strategie;

class Asservissement{
    public:
        Distance vitesse_lineaire_a_atteindre;
        Angle vitesse_angulaire_a_atteindre;
        Distance vitesse_lineaire_max;
        Angle vitesse_angulaire_max;
        Distance acceleration_lineaire;
        Angle acceleration_angulaire;
        float linearDutySent, angularDutySent;
        PIDFilterDistance pid_filter_distance;
        PIDFilterAngle pid_filter_angle;
#ifdef ROBOTHW
        Roues roues;
        Capteurs capteurs;
#endif
        float seuil_collision;
        unsigned int buffer_collision;
        unsigned int nb_echantillons_buffer_collision;

        Position destination;
        Angle destAngle;
        bool en_mouvement;
        bool direction;
        bool stop;
    public:
        Strategie* strategie;
        short toto;
        Odometrie* odometrie;
        Asservissement(Odometrie* _odemetrie);
        static Asservissement * asservissement;
        static const uint16_t nb_ms_between_updates;
        void update(void);
        void goTo(Position position, bool stop=true);
        void goToDirection(Angle angle);
        void recule(Distance distance);
        void tourne(Angle angle);
        Distance getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant);
        Angle getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant);
};

#endif // ASSERVISSEMENT_H_INCLUDED
