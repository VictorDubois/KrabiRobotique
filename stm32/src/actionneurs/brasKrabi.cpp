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


    BrasKrabi::BrasKrabi(){}

    void BrasKrabi::expand(){}

    void BrasKrabi::collapse(){}

    void BrasKrabi::front(){}

#endif
