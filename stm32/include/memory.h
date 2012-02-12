#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <stddef.h>



/**@brief typedef for alignment to long boundary */
typedef long Align;

union header {
    struct {
        union header *nextFree;
        unsigned size;
        } s;
    Align x; /*The Align field is never used; it just forces each header to be aligned on a worst-case boundary.
*/
};

typedef union header Header;

extern "C" Header _end;

extern Header *memory_ptr;

///@defgroup allocators standard memory allocators
///@brief Groups all the standards cpp functions to dynamically allocate memory on the heap.
void * operator new(size_t size) throw();
void * operator new[](size_t size) throw();
void operator delete(void * p)    throw();
void operator delete[](void * p)    throw();




#endif // MEMORY_H_INCLUDED
