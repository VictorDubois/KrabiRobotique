#ifndef BRASTAPIS_H
#define BRASTAPIS_H

#include "brasKrabi.h"

#ifdef ROBOTHW
    #include "servo.h"


/** @class BrasTapis La classe BrasTapis permet de controler les bras sur l'avant de Krabi
*/
class BrasTapis
{
    public:
        /** @brief Constructeur
          * @fn BrasTapis()
        */
        BrasTapis();

        /** @brief Destructeur
        */
        ~BrasTapis();



        /// @brief getLeft() renvoit le BrasTapisGauche courant
        BrasKrabi *getLeft();

        /// @brief getLeft() renvoit le BrasTapisDroit courant
        BrasKrabi *getRight();

        void expand();
        void collapse();
        void front();

    private:
        static BrasKrabi *brasTapisLeft;
        static BrasKrabi *brasTapisRight;
};
#else

class BrasTapis
{
    public:
        BrasTapis();
        ~BrasTapis();

    private:
        static BrasKrabi *brasTapisLeft;
        static BrasKrabi *brasTapisRight;

        /// @brief getLeft() renvoit le brasTapisGauche courant
        static BrasKrabi *getLeft();

        /// @brief getLeft() renvoit le brasTapisDroit courant
        static BrasKrabi *getRight();

        void expand();
        void collapse();
        void front();
};

#endif

#endif // BRASTAPIS_H

