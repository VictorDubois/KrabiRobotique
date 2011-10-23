#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <stddef.h>

extern "C" char _end;

extern char *memory_ptr;

///@defgroup allocators standard memory allocators
///@brief Groups all the standards cpp functions to dynamically allocate memory on the heap.
//@{
void * operator new(size_t size) throw();
void * operator new[](size_t size) throw();
void operator delete(void * p)    throw();
void operator delete[](void * p)    throw();

#endif // MEMORY_H_INCLUDED
