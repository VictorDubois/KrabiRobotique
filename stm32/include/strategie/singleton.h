#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

template <typename T>
class Singleton
{
    protected:
    // Constructor/Destructor
    Singleton();
    ~Singleton();

    public:
    // Function to get the only instance
    static T *getInstance();

    // Function to kill the instance
    static void kill();

    private:
    // Unique instance
    static T *_singleton;
};

template <typename T>
T *Singleton<T>::_singleton = NULL;

#endif
