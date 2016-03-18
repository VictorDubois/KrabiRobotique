#ifndef KJ2016TEMPO_H
#define KJ2016TEMPO_H

/**
 * @brief Runs the strategy for Krabi Junior 2016
 *
 * No odometry or feedback this year on this bot. It's fully temporised and driven by continuous servos.
 */
class KJ2016Tempo
{
    unsigned int LEFT_SERVO_ID;
    unsigned int RIGHT_SERVO_ID;

    public:
        /**
         * @brief Runs the strategy
         */
        static void run(bool isYellow);

        ~KJ2016Tempo();

    private:

        void enginesStart();
        void enginesStop();

        void turn90(bool toLeft);

        void move(int distance);

        void wasteTime(unsigned int time);

        KJ2016Tempo(unsigned int leftServoID, unsigned int rightServoID);
};

#endif // KJ2016TEMPO_H
