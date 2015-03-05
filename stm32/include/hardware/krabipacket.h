#ifndef KRABIPACKET_H
#define KRABIPACKET_H

#include <stdint.h>

#define KRABIPACKET_MAXSIZE 128
#define KRABIPACKET_FIXEDBASESIZE 3
#define KRABIPACKET_HEADER_MAXSIZE 3

class KrabiPacket
{
    public:
        KrabiPacket();
        virtual ~KrabiPacket();

        void reset();

        void setId(uint8_t id);

        void add(char* data);
        void add(int data);
        void add(float data);
        void add(uint8_t data);
        void add(uint32_t data);

        uint8_t getId();

        //void* readNext();

        uint16_t getLength();
        uint8_t* getPacket();
    protected:
    private:
        uint8_t *packet;
        uint16_t length;
        uint8_t id;
};

#endif // KRABIPACKET_H
