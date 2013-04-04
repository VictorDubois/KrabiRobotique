#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#ifndef NULL
#define NULL 0
#endif

#include "memory.h"

template <typename T>
class Singleton
{
    protected:
    // Constructor/Destructor
    Singleton() {}
    ~Singleton() {}

    public:
    // Function to get the only instance
    static T *getInstance()
    {
        if (NULL == _singleton) // if the instance does not exist
        {
            _singleton = new T; // create singleton
        }

        return (static_cast<T*> (_singleton));
    }

    // Function to kill the instance
    static void kill()
    {
        if (NULL != _singleton)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }

    private:
    // Unique instance
    static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#endif
