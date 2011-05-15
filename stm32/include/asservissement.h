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
#include "command.h"

class Strategie;

class Asservissement{
    public:
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

    public:
        Strategie* strategie;
        short toto;
        Odometrie* odometrie;
	Command* command;
        Asservissement(Odometrie* _odometrie);

	float getLinearSpeed()
	{
		return command ? command->getLinearSpeed() : 0;
	}

	Angle getAngularSpeed()
	{
		return command ? command->getAngularSpeed() : 0;
	}

        static Asservissement * asservissement;
        static const uint16_t nb_ms_between_updates;
        void update(void);
};

#endif // ASSERVISSEMENT_H_INCLUDED
