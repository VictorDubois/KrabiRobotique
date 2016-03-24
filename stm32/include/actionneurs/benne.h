#ifndef BENNE_H
#define BENNE_H

class MicroSwitch;

class Benne
{
    /**
      * The ID of the AX12 used to drive the belts
    */
    static const int BELTS_SERVO_ID = 0; // To update

    static const int FORWARD_SPEED  = 1023;
    static const int BACKWARD_SPEED = 2046;

    /**
      * The ID of the AX12 used to deploy/retract the front ramp
    */
    static const int RAMP_LEFT_SERVO_ID     = 0; // To update
    static const int RAMP_RIGHT_SERVO_ID    = 0; // To update

    static const int RAMP_LEFT_DEPLOYED_ANGLE    = 0;
    static const int RAMP_LEFT_RETRACTED_ANGLE   = 1023;

    static const int RAMP_RIGHT_DEPLOYED_ANGLE   = 1023;
    static const int RAMP_RIGHT_RETRACTED_ANGLE  = 0;

    public:
        struct Status
        {
            enum Enum
            {
                UNKNOWN,
                OPEN,
                CLOSED,
                OPENING,
                CLOSING
            };
        };

        static Benne* getInstance();

        ~Benne();

        void update();

        void setBenneEmpty();
        void setBenneFull();

        bool getIsBenneEmpty() const;
        bool getIsBenneFull() const;

        void empty();
        void open();

        void stop();

        void deployRamp();
        void retractRamp();

        Benne::Status::Enum getStatus() const;

    protected:
        bool isFrontSwitchActive() const;
        bool isBackSwitchActive() const;

    private:
        Benne();

        void setStatus(Status::Enum status);

        bool isBenneEmpty;

        Status::Enum m_status;

        MicroSwitch* m_backSwitch;
        MicroSwitch* m_frontSwitch;
};

#endif // BENNE_H
