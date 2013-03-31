#include "singleton.h"

Singleton::Singleton() 
{ 
}
Singleton::~Singleton() 
{ 
}

static T* Singleton::getInstance()
{
    if (NULL == _singleton) // if the instance does not exist
    {
        _singleton = new T; // create singleton
    }

    return (static_cast<T*> (_singleton));
}

static void Singleton::kill()
{
    if (NULL != _singleton)
    {
        delete _singleton;
        _singleton = NULL;
    }
}
