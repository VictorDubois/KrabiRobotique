#ifndef BRASKRABI_H
#define BRASKRABI_H

#ifdef ROBOTHW
    #include "servo.h"


/** @class BrasKrabi : La classe BrasKrabi est une classe générique utilisée par BrasAvant
*/
class BrasKrabi
{
    public:
        /** @brief Constructeur
          * @fn BrasKrabi(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded)
        */
        BrasKrabi(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront);

        /** @brief Destructeur
        */
        ~BrasKrabi();

        Servo* servo;
        float angleCollapsed, angleExpanded, angleFront;

        /// @brief expand() Déploie le bras à 90°
        void expand();

        /// @brief collapse() Replie le bras
        void collapse();

        /// @brief front() Déploie le bras à 180°
        void front();

};
#else

class BrasKrabi
{
    public:
        BrasKrabi();
        ~BrasKrabi();

    protected:
    private:
        void expand();
        void collapse();
        void front();

};

#endif

#endif // BRASKRABI_H

