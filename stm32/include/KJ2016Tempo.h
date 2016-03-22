#ifndef KJ2016TEMPO_H
#define KJ2016TEMPO_H

/**
 * @brief Runs the strategy for Krabi Junior 2016
 *
 * No odometry or feedback this year on this bot. It's fully temporised and driven by continuous servos.
 */
class KJ2016Tempo
{
    static const float KJ_INTERAXIS        = 132.f; // To update
    static const float KJ_WHEEL_DIAMETER   = 70.f;
    static const float SERVO_MAX_RPM       = 52.f;

    public:
        /**
         * @brief Runs the strategy
         */
        static void run(bool isYellow);

    private:
        const unsigned int LEFT_SERVO_ID;
        const unsigned int RIGHT_SERVO_ID;
        const float SERVO_SPEED_FACTOR;

        void stop();

        void turn90(bool toLeft);

        void move(int distance);

        void waitForArrival(unsigned int duration);

        KJ2016Tempo(unsigned int leftServoID, unsigned int rightServoID);
};

#endif // KJ2016TEMPO_H
