#include "bras2.h"

#ifdef ROBOTHW

    Bras2::Bras2(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront)
        : angleCollapsed(angleCollapsed), angleExpanded(angleExpanded), angleFront(angleFront)
    {
        this->servo = new Servo(timer, OCx, RC0degre, RC180degres);
    }

    void Bras2::expand()
    {
        servo->goToAngle(angleExpanded);
    }

    void Bras2::collapse()
    {
        servo->goToAngle(angleCollapsed);
    }

    void Bras2::front()
    {
        servo->goToAngle(angleFront);
    }

#else

#include <QDebug>

    Bras2::Bras2()
    {}

    void Bras2::expand()
    {
#ifndef ROBOTHW
    qDebug() << "Bras lateral sorti";
#endif
    }

    void Bras2::collapse()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral rentré";
#endif
    }

    void Bras2::front()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral sorti à 180°";
#endif
    }

#endif
