#ifndef CONTAINER_H
#define CONTAINER_H

#ifdef ROBOTHW
    #include "servo.h"

    class Container
    {
        public:
            static Container* getSingleton();

            void open();
            void close();

        protected:
        private:
            static Container* singleton;
            Container();

            Servo* servo;

    };
#else
#include <QDebug>
    class Container
    {
        public:
            static Container* getSingleton();

            void open();
            void close();

        protected:
        private:
            static Container* singleton;
            Container();

    };

#endif

#endif // CONTAINER_H
