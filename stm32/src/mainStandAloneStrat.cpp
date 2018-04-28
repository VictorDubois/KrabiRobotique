#include "etape.h"
#include "dijkstra.h"
#include "goldo2018.h"
#include "positionPlusAngle.h"
#include "constantes.h"
//#define ALLOW_DEBUG
#ifdef ALLOW_DEBUG
    #include "debug.h"
#endif

#define POSITIONNEMENT

#define DISABLE_TIRETTE

#ifdef USE_IOSTREAM
    #include <iostream>
#endif

#define SERIAL_STREAM
#ifdef SERIAL_STREAM
    #include "serialComStrat.h"
    #include "serialMessage.h"
#endif

// Dit si on est du coté bleu
bool isBlue() // = ROUGE
{
    return true;
}

/**
 * Update the strategy, and send the new mission
 * @param StrategieV3* strat, the strategy
 * @param SerialComStrat *serialComStrat
 * @return result, the strategie's update result
 */
int sendNewMission(StrategieV3* strat, SerialComStrat *serialComStrat) {
    int result = strat->update();
    Position goal = strat->getEtapeEnCours()->getPosition();
    int mission_type = strat->getEtapeEnCours()->getEtapeType();

    #ifdef USE_IOSTREAM
    std::cout << "goal: " << goal.Print() << std::endl;
    std::cout << "type: " << mission_type << std::endl;
    #endif // USE_IOSTREAM

    PositionPlusAngle* goalWithAngle = new PositionPlusAngle(goal, 0);
    serialComStrat->sendNewMission(*goalWithAngle, mission_type);

    return result;
}

int main()
{
    #ifdef USE_IOSTREAM
        std::cout << "begin" << std::endl;
    #endif // USE_IOSTREAM

    Position pos(200,1850, isBlue());//1500, isBlue());
    PositionPlusAngle posPlusAngle(pos,-M_PI/2);
    if (!isBlue())
        posPlusAngle = PositionPlusAngle(pos,-M_PI/2);

    StrategieV3* strat = new Goldo2018(isBlue());

#ifdef SERIAL_STREAM
    int result;

    // strategy serial com handler
    SerialComStrat *serialComStrat = new SerialComStrat();
    SerialMessage* messageReceived;

// Tests
//    SerialMessage* message = new SerialMessage(SerialMessage::ASK_NEXT_MISSION, 0, NULL);
//    serialComStrat->sendNewMission(posPlusAngle, strat->getEtapeEnCours()->getEtapeType());


    while(1) {
        // Receive a new message (blocking)
        serialComStrat->receiveMessage(&messageReceived);

        // Act according to the message's type
        switch(messageReceived->getType()) {
            case SerialMessage::ASK_NEXT_MISSION:
                #ifdef USE_IOSTREAM
                    std::cout << "ASK_NEXT_MISSION" << std::endl;
                #endif // USE_IOSTREAM
                sendNewMission(strat, serialComStrat);
                break;

            case SerialMessage::OBSTACLE_DETECTED:
                #ifdef USE_IOSTREAM
                    std::cout << "OBSTACLE_DETECTED" << std::endl;
                #endif // USE_IOSTREAM
                strat->collisionAvoided();
                sendNewMission(strat, serialComStrat);
                break;

            default:
                break;
        }
    }

#endif

    return 0;
}


