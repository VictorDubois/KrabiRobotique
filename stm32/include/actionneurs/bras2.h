#ifndef BRAS2_H
#define BRAS2_H

#ifdef ROBOTHW
    #include "servo.h"


/** @class Bras2 : La classe Bras2 est une classe générique utilisée par BrasAvant
*/
class Bras2
{
    public:
        /** @brief Constructeur
          * @fn Bras2(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded)
        */
        Bras2(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront);

        /** @brief Destructeur
        */
        ~Bras2();

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

class Bras2
{
    public:
        Bras2();
        ~Bras2();

    protected:
    private:
        void expand();
        void collapse();
        void front();

};

#endif

#endif // BRAS2_H
