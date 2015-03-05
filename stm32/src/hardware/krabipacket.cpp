#ifdef NOTYETIMPLEMENTED
#include "krabipacket.h"

KrabiPacket::KrabiPacket()
{
    packet = new uint8_t[KRABIPACKET_MAXSIZE];
    header = new uint8_t[KRABIPACKET_HEADER_MAXSIZE];

    length = 0;
    lengthHeader = 0; //Def, type ?
}

KrabiPacket::~KrabiPacket()
{
    delete [] packet;
    delete [] header;
}

void KrabiPacket::add(char* data)
{
    int size = 0;
    while( data[size] != '\0' )
        size ++;
    if (length + size >= KRABIPACKET_MAXSIZE || lengthHeader + 2 >= KRABIPACKET_HEADER_MAXSIZE) return;

    for(int i=0; i<size; i++)
        packet[length + i] = data[i];

    header[lengthHeader] = 's';
    header[lengthHeader + 1] = size;

    length += size;
    lengthHeader += 2;
}

void KrabiPacket::add(int data)
{
    add((uint32_t) data);
}

void KrabiPacket::add(uint8_t data)
{
    if (length + 1 >= KRABIPACKET_MAXSIZE || lengthHeader + 1 >= KRABIPACKET_HEADER_MAXSIZE) return;

    packet[length] = data;
    header[lengthHeader] = 'b';

    length += 1;
    lengthHeader++;
}

void KrabiPacket::add(uint32_t data)
{
    if (length + 4 >= KRABIPACKET_MAXSIZE || lengthHeader + 1 >= KRABIPACKET_HEADER_MAXSIZE) return;

    for(int i=0; i<4; i++)
    {
        packet[length + 3 - i] = (uint8_t)(data % 256);
        data >>= 8;
    }
    header[lengthHeader] = 'i';

    length += 1; // 4 plutôt non ???????
    lengthHeader++;
}

uint16_t KrabiPacket::getLength()
{
    //Pourquoi int16 ???
    /* FIXEDBASE = 3 cf getPacket() */
    return KRABIPACKET_FIXEDBASESIZE + lengthHeader + length;
}

uint8_t* KrabiPacket::getPacket()
{
    uint8_t* final = new uint8_t[KRABIPACKET_MAXSIZE];

    /*Final de taille lengthHeader + length + 3
    (FIXEDBASESIZE == 3) donc de taille final[0] */
    //Longueur totale du packet final
    final[0] = getLength();//TODO : int 16 dans int8
    //Longueur du header
    final[1] = lengthHeader;//TODO : Taille,type ??? initialisé jamais défini
    uint8_t checksum = 0;
    //Ecriture du packet et calcul de la CS
    for(int i=0; i<lengthHeader; i++)
    {
        final[2+i] = header[i];
        checksum += header[i];
    }
    for(int i=0; i<length; i++)
    {
        final[2+lengthHeader+i] = packet[i];
        checksum += packet[i];
    }
    //Ecriture de la CS
    final[2+lengthHeader+length] = checksum;

    return final;
}
#endif
