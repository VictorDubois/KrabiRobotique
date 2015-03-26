#ifndef BRASTAPIS_H
#define BRASTAPIS_H

#include "brasKrabi.h"

#ifdef ROBOTHW
    #include "servo.h"


/** @class BrasTapis La classe BrasTapis permet de controler les bras sur l'avant de Krabi
*/
class BrasTapis : public BrasKrabi
{
    public:
        /** @brief Constructeur
          * @fn BrasTapis()
        */
        BrasTapis(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres, float angleCollapsed, float angleExpanded);

        /** @brief Destructeur
        */
        ~BrasTapis();

        static void initBrasTapis();

        /// @brief getLeft() renvoit le BrasTapisGauche courant
        BrasTapis *getLeft();

        /// @brief getLeft() renvoit le BrasTapisDroit courant
        BrasTapis *getRight();

        void expand();
        void collapse();
        void front();

    private:
        static BrasTapis *brasTapisLeft;
        static BrasTapis *brasTapisRight;
};
#else

class BrasTapis
{
    public:

        static void initBrasTapis();
        static BrasTapis *brasTapisLeft;
        static BrasTapis *brasTapisRight;

        /// @brief getLeft() renvoit le brasTapisGauche courant
        static BrasTapis *getLeft();

        /// @brief getLeft() renvoit le brasTapisDroit courant
        static BrasTapis *getRight();

        void expand();
        void collapse();
        void front();

    private :
        BrasTapis();
        ~BrasTapis();

};

#endif

#endif // BRASTAPIS_H

