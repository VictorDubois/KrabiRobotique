#ifndef BRASLATERAUX_H
#define BRASLATERAUX_H

#ifdef ROBOTHW
    #include "servo.h"

    /// @brief La classe BrasLateraux permet de controler les bras latéraux de Krabi / KrabiJr
    class BrasLateraux
    {
        public:
            /// @brief expand() Déploie le bras à 90°
            void expand();

            /// @brief collapse() Replie le bras
            void collapse();

            /// @brief front() Déploie le bras à 180°
            void front();

            static void initBrasLateraux();
            static BrasLateraux* getLeft();
            static BrasLateraux* getRight();

        protected:
        private:
            static BrasLateraux *left, *right;

            BrasLateraux(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded, float angleFront);

            Servo* servo;
            float angleCollapsed, angleExpanded, angleFront;
    };
#else

    class BrasLateraux
    {
        public:
            BrasLateraux();

            void expand();
            void collapse();
            void front();

            static void initBrasLateraux();
            static BrasLateraux* getLeft();
            static BrasLateraux* getRight();

        protected:
        private:
            static BrasLateraux *left, *right;
    };

#endif

#endif // BRASLATERAUX_H
