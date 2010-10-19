#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <cstddef>

extern "C" char _end;

extern char *memory_ptr;

///@defgroup allocators standard memory allocators
///@brief Groups all the standards cpp functions to dynamically allocate memory on the heap.
//@{
inline void * operator new(size_t size) throw()
{
    void *ptr = (void *)memory_ptr;
    memory_ptr += size;
    return ptr;
}

inline void * operator new[](size_t size) throw()
{
    void *ptr = (void *)memory_ptr;
    memory_ptr += size;
    return ptr;
}

inline void operator delete(void * p)    throw()
{
}

inline void operator delete[](void * p)    throw()
{
}

//placement new
/* inline void* operator new(size_t, void* p)   throw()
{
    return p;
}

inline void* operator new[](size_t, void* p) throw()
{
    return p;
}

inline void  operator delete(void*, void*) throw() { };

inline void  operator delete[](void*, void*) throw() { };
*/
//@}

#endif // MEMORY_H_INCLUDED
