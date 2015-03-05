#ifndef BRASLATERAL_H
#define BRASLATERAL_H

#ifdef ROBOTHW
    #include "servo.h"

    /// @brief La classe BrasLateral permet de controler les bras latéraux de Krabi / KrabiJr
    class BrasLateral
    {
        public:
            /// @brief expand() Déploie le bras à 90°
            void expand();

            /// @brief collapse() Replie le bras
            void collapse();

            /// @brief front() Déploie le bras à 180°
            void front();

            static void initBrasLateraux();
            static BrasLateral* getLeft();
            static BrasLateral* getRight();

        protected:
        private:
            static BrasLateral *left, *right;

            BrasLateral(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront);

            Servo* servo;
            float angleCollapsed, angleExpanded, angleFront;
    };
#else

    class BrasLateral
    {
        public:
            BrasLateral();

            void expand();
            void collapse();
            void front();

            static void initBrasLateraux();
            static BrasLateral* getLeft();
            static BrasLateral* getRight();

        protected:
        private:
            static BrasLateral *left, *right;
    };

#endif

#endif // BRASLATERAL_H
