#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#ifdef ROBOTHW
#include "quadrature_coder_handler.h"
#endif

#include <stdint.h>

class Asservissement;

class Strategie {
    private:
    bool is_blue;
    Asservissement* asservissement;
    void doNext();
    int instruction_nb;
    bool collision_detected;
    int instruction_collision_nb;

    public:
    void collisionDetected();
    Strategie(bool is_blue, Asservissement* asservissement);
    void foundOtherRobot();
    void done();
    void doNthInstruction(uint16_t n);
    void theEnd();
};

#endif // STRATEGIE_H_INCLUDED
