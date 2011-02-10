#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#ifdef ROBOTHW
#include "quadrature_coder_handler.h"
#endif

#include <stdint.h>

class Command;
class Odometrie;

class Strategie {
    private:
    bool is_blue;
    Command* command;
    void doNext();
    int instruction_nb;
    bool collision_detected;
    int instruction_collision_nb;

    public:
    void collisionDetected();
    Strategie(bool is_blue, Command* command, Odometrie* odometrie);
    void foundOtherRobot();
    void done();
    void doNthInstruction(uint16_t n);
    void theEnd();
};

#endif // STRATEGIE_H_INCLUDED
