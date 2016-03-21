#ifndef FICHINGNET_H
#define FICHINGNET_H

/**
 * @brief This singleton class handles the fishing net actuator.
 * @see getSingleton
 */
class FishingNet
{
    /**
      * The ID of the innermost AX12 (i.e. for rotation)
      */
    static const int SERVO_INT_ID = 42; // To update
    /**
      * The ID of the outermost AX12 (i.e. for folding/unfolding)
      */
    static const int SERVO_EXT_ID = 16;

    /**
      * Those constantes are angles sent to the relevant servos for the relevant action (names are pretty explicit)
      */
    static const int SERVO_EXT_CLOSED_POS   = 0x0339;
    static const int SERVO_EXT_DEPLOYED_POS = 0x0200;
    static const int SERVO_EXT_RAISED_POS   = 0x0240;

    static const int SERVO_INT_RAISED_POS   = 0x0200;
    static const int SERVO_INT_LOWERED_POS  = 0x00C3;

    public:
        enum NET_STATE
        {
            CLOSED,
            OPENED,
            RAISED,
            NET_LOWERED
        };

        /**
         * @brief FishingNet is a singleton. This static method will return the only possible instance of FishingNet (and create it if deemed necessary)
         */
        static FishingNet* getSingleton();

        /**
         * @brief Closes the arm (folds it against the robot)
         */
        void close();

        /**
         * @brief Deploys the arm and gets the net ready to fish
         */
        void deploy();

        /**
         * @brief Lower the net (start to fish)
         */
        void lowerNet();
        /**
         * @brief Raise the net (finnish fishing)
         */
        void raiseNet();

        /**
         * @brief Raise the net's arm (to avoid hitting the tank's sides)
         */
        void raiseArm();

        /**
         * @brief Returns the current software state of the device. Note it may not reflect the actual positions of the servos.
         * @see NET_STATE
         */
        NET_STATE getCurrentState() const;

    private:

        /**
         * @brief Constructor
         * @see getSingleton
         */
        FishingNet();

        /**
         * @brief Move (i.e. lower or raise) the arm to a set angle
         * @param destAngle The angle (as used by the AX12)
         */
        void moveArm(int destAngle);

        /**
         * @brief Rotate (i.e. turn on itself) the arm to a set angle
         * @param destAngle The angle (as used by the AX12)
         */
        void rotateArm(int destAngle);

        /**
         * @brief The software state of this device may not reflect its hardware state (servo locked, etc.).
         *
         * This function will NOT move the servos, do not call it directly.
         * @param The new software state of the device
         */
        void setCurrentState(NET_STATE state);

        NET_STATE m_currentState;
};

#endif
