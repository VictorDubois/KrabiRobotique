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
    SerialComStrat *serialComStrat = new SerialComStrat();
    char messageData[2];
    messageData[0] = SerialComStrat::ASK_NEXT_MISSION;
    messageData[1] = 200;

    SerialMessage* message = new SerialMessage(SerialMessage::ASK_NEXT_MISSION, 0, NULL);
    serialComStrat->sendNewMission(posPlusAngle);

//    serialComStrat->sendMessage(message);
//
//    delete message;
//
//    message = new SerialMessage(SerialMessage::NEW_MISSION, 2, messageData);
//    serialComStrat->sendMessage(message);
//
//    delete message;



//    SerialCom *serialCom = new SerialCom();
//
//    char message = 100;
//    serialCom->sendSerial(message);
//    serialCom->sendSerial(message);
//    serialCom->sendSerial(serialCom->receiveSerial());
#endif

    int result;
    result = strat->update();
    result = strat->update();

    strat->collisionAvoided();

    result = strat->update();

    #ifdef USE_IOSTREAM
        std::cout << "goal: " << strat->getEtapeEnCours()->getPosition().Print() << std::endl;
        std::cout << "end" << std::endl;
    #endif // USE_IOSTREAM
    return 0;
}


