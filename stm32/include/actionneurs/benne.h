#ifndef BENNE_H
#define BENNE_H

class MicroSwitch;

class Benne
{
    /**
      * The ID of the AX12 used to drive the belts
    */
    static const int SERVO_ID = 0; // To update

    static const int FORWARD_SPEED  = 1023;
    static const int BACKWARD_SPEED = 2046;

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

        bool isFrontSwitchActive() const;
        bool isBackSwitchActive() const;

        Benne::Status::Enum getStatus() const;

    private:
        Benne();

        void setStatus(Status::Enum status);

        bool isBenneEmpty;

        Status::Enum m_status;

        MicroSwitch* m_backSwitch;
        MicroSwitch* m_frontSwitch;
};

#endif // BENNE_H
