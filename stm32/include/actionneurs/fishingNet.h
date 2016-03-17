#ifndef FICHINGNET_H
#define FICHINGNET_H

class FishingNet
{
    static const int SERVO_INT_ID = 0; // To update
    static const int SERVO_EXT_ID = 1;

    static const int SERVO_EXT_CLOSED_POS   = 0x00;
    static const int SERVO_EXT_DEPLOYED_POS = 0x00;
    static const int SERVO_EXT_RAISED_POS   = 0x00;

    static const int SERVO_INT_RAISED_POS   = 0x00;
    static const int SERVO_INT_LOWERED_POS  = 0x00;

    public:      
        FishingNet();

        enum NET_STATE
        {
            CLOSED,
            OPENED,
            RAISED,
            NET_LOWERED
        };

        static FishingNet* getSingleton();

        void close();
        void deploy();

        void lowerNet();
        void raiseNet();

        void raiseArm();

    private:

        void moveArm(int destAngle);
        void rotateArm(int destAngle);

        NET_STATE m_currentState;
};

#endif
