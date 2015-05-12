#ifndef KRABIPACKET_H
#define KRABIPACKET_H

#include <stdint.h>

#define KRABIPACKET_MAXSIZE 32
#define KRABIPACKET_SUFFIX_SIZE 1

#ifndef ROBOTHW
    #include <QByteArray>
#endif

class KrabiPacket
{
public:
    enum PACKET_TYPE {
        PING_NULL = 0,
        PING_SET = 1,

        REMOTE_MOD_SET = 2,
        REMOTE_MOD_RESET = 3,

        REMOTE_CONTROL_SET = 4,
        REMOTE_CONTROL_RESET = 5,

        LOG_NORMAL = 10,
        LOG_DEBUG = 11,

        WATCH_VARIABLE = 20,
        WATCH_VARIABLE_TIMED = 21,
        WATCH_REQUIRE_ONCE = 23,

        WATCH_SET = 24,
        WATCH_RESET = 25,

        WATCH_DESELECT_ALL = 27,

        SET_ODOMETRIE = 30,
        SET_PID_LIN = 32,
        SET_PID_ANG = 33,

        ASSERV_RESULT = 38,

        TIME_RESET = 40,
        TIME_SYNC = 41,

        RUN_PID_TEST = 50,
        RUN_GOTO = 51,

        STOP = 100
    };

    enum W_TABLE {
        W_NULL,
        W_WATCHES,
        W_POSITION,
        W_SPEED,
        W_SPEED_TARGET,
        W_ODOMETRIE,
        W_PID_LIN,
        W_PID_ANG,
        W_SHARPS,
        MAX_WATCHES
    };

    enum DATA_TYPE {
        DATA_INT8,
        DATA_INT16,
        DATA_INT32,
        DATA_FLOAT,
        DATA_DOUBLE,
        DATA_STRING
    };

    KrabiPacket(uint8_t* data, uint8_t size);
    KrabiPacket(uint8_t id = PING_NULL, W_TABLE watch = W_NULL);
#ifndef ROBOTHW
    KrabiPacket(QByteArray data);
#endif

    void addData(void* data, uint8_t size);
    void copyData(void* dest, uint8_t size);

    // args
    template<typename T>
    void add(T data)
    {
        addData(&data, sizeof(T));
    }

    template<typename T>
    T get()
    {
        T d;
        copyData(&d, sizeof(T));
        return d;
    }

    template<typename T>
    bool isReadable()
    {
        return mCursor + sizeof(T) < mLength;
    }

    void addString(char* data);
    char* getString();

    void setId(uint8_t id);
    uint8_t id();

    uint8_t length();
    uint8_t* data();

    bool checkValidity();

#ifndef ROBOTHW
    QByteArray dataByteArray();
#endif

    bool isValid();

private:
    uint8_t mPacket[KRABIPACKET_MAXSIZE], mPacketSecurized[KRABIPACKET_MAXSIZE];
    uint8_t mId, mCursor, mLength, mLengthSecurized;
    bool mValid;

    void securize();
    void unsecurize();
};

#endif // KRABIPACKET_H
