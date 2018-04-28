#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <SerialStream.h>
using namespace LibSerial;

class SerialCom
{
public:
//    /// @brief Retourne la valeur de l'angle dans un float entre -PI et PI.
//    static SerialCom wrapSerialCom(SerialCom angle);
//
//    /// @brief Vérifie s'il y a égalité ou presque entre deux angles.
//    static bool anglesAlmostEqual(SerialCom a1, SerialCom a2);
//
//    /// @brief Calcul la différence entre deux angles (rad), le résultat est donné dans [-pi, pi]
//    static float diffSerialCom(float a, float b);

    char receiveSerial();
    void sendSerial(char sendByte);
    void sendSerial(char* write_byte);


    SerialCom();
    ~SerialCom();

private:
    SerialStream serial_stream;

};

#endif // SERIALCOM_H

