#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#ifdef ROBOTHW
#include "quadrature_coder_handler.h"
#endif

#include <stdint.h>

class Odometrie;
class Pince;

class Strategie {
    private:
    bool is_blue;
    void doNext();
    int instruction_nb;
    bool collision_detected;
    int instruction_collision_nb;
    Pince* pince;

    public:
    static Strategie* strategie;

    void collisionDetected();
    Strategie(bool is_blue, Odometrie* odometrie, Pince* pince);
    void grab(Pince* pince);
    void foundOtherRobot();
    void done();
    void doNthInstruction(uint16_t n);
    void theEnd();
};

#endif // STRATEGIE_H_INCLUDED
