#ifndef BRASAVANT_H
#define BRASAVANT_H

#include "bras2.h"

#ifdef ROBOTHW
    #include "servo.h"


/** @class BrasAvant La classe BrasAvant permet de controler les bras sur l'avant de Krabi
*/
class BrasAvant
{
    public:
        /** @brief Constructeur
          * @fn BrasAvant()
        */
        BrasAvant();

        /** @brief Destructeur
        */
        ~BrasAvant();



        /// @brief getLeft() renvoit le brasAvantGauche courant
        Bras2 *getLeft();

        /// @brief getLeft() renvoit le brasAvantDroit courant
        Bras2 *getRight();

        void expand();
        void collapse();
        void front();

    private:
        static Bras2 *brasAvantLeft;
        static Bras2 *brasAvantRight;
};
#else

class BrasAvant
{
    public:
        BrasAvant();
        ~BrasAvant();

    private:
        static Bras2 *brasAvantLeft;
        static Bras2 *brasAvantRight;

        /// @brief getLeft() renvoit le brasAvantGauche courant
        static Bras2 *getLeft();

        /// @brief getLeft() renvoit le brasAvantDroit courant
        static Bras2 *getRight();

        void expand();
        void collapse();
        void front();
};

#endif

#endif // BRASAVANT_H

