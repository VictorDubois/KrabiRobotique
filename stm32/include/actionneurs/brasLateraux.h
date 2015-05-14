#ifndef BRASLATERAUX_H
#define BRASLATERAUX_H

#ifdef ROBOTHW
    #include "servo.h"

    /// @brief La classe BrasLateraux permet de controler les bras latéraux de Krabi / KrabiJr
    class BrasLateral
    {
        friend class BrasLateraux;
        public:
            /// @brief expand() Déploie le bras à 90°
            void expand();

            /// @brief collapse() Replie le bras
            void collapse();

            /// @brief front() Déploie le bras à 180°
            void front();

            Servo* servo;

        protected:
        private:
            BrasLateral(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront);

            float angleCollapsed, angleExpanded, angleFront;
    };
#else

    class BrasLateral
    {
        friend class BrasLateraux;
        public:
            BrasLateral();

            void expand();
            void collapse();
            void front();
    };

#endif

class BrasLateraux
{
public:
    static BrasLateral* getLeft();
    static BrasLateral* getRight();

private:
    static void initBrasLateraux();
    static BrasLateral *left, *right;
};

#endif // BRASLATERAUX_H
