#include "brasKrabi.h"

#ifdef ROBOTHW

    BrasKrabi::BrasKrabi(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront)
        : angleCollapsed(angleCollapsed), angleExpanded(angleExpanded), angleFront(angleFront)
    {
        this->servo = new Servo(timer, OCx, RC0degre, RC180degres);
    }

    void BrasKrabi::expand()
    {
        servo->goToAngle(angleExpanded);
    }

    void BrasKrabi::collapse()
    {
        servo->goToAngle(angleCollapsed);
    }

    void BrasKrabi::front()
    {
        servo->goToAngle(angleFront);
    }

#else

#include <QDebug>

    BrasKrabi::BrasKrabi()
    {}

    void BrasKrabi::expand()
    {
#ifndef ROBOTHW
    qDebug() << "Bras lateral sorti";
#endif
    }

    void BrasKrabi::collapse()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral rentré";
#endif
    }

    void BrasKrabi::front()
    {
#ifndef ROBOTHW
    qDebug() << "Bras Lateral sorti à 180°";
#endif
    }

#endif
