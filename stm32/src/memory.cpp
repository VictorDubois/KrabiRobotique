#include "memory.h"

char *memory_ptr = &_end; // fin du programme (et début du tas)

void * operator new(size_t size) throw()
{
    void *ptr = (void *)memory_ptr;
    memory_ptr += size;
    return ptr;
}

void * operator new[](size_t size) throw()
{
    void *ptr = (void *)memory_ptr;
    memory_ptr += size;
    return ptr;
}

void operator delete(void * p)    throw()
{
}

void operator delete[](void * p)    throw()
{
}
