#ifndef PARASOL_H
#define PARASOL_H

/**
 * @brief This singleton class handles the parasol actuator.
 * @see getSingleton
 */
class Parasol
{
    /**
      * The ID of the servo
      */
    static const int SERVO_ID = 0; // To update


    /**
      * Those constantes are angles for the relevant action (names are pretty explicit)
      */
    static const int SERVO_CLOSED_POS   = 0x00;
    static const int SERVO_DEPLOYED_POS = 0x00;


    public:

        /**
         * @brief Parasol is a singleton. This static method will return the only possible instance of Parasol (and create it if deemed necessary)
         */
        static Parasol* getSingleton();

        /**
         * @brief Closes the parasol
         */
        void close();

        /**
         * @brief Deploys the parasol
         */
        void deploy();

    private:

        /**
         * @brief Constructor
         * @see getSingleton
         */
        Parasol();

};

#endif
