#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED


class Angle
{
    private:
    float angle;

    public:
    Angle();
    Angle(float angle);
    Angle operator+(const Angle &angle);
    Angle operator-(const Angle &angle);
    Angle operator-() const;
    Angle operator=(const Angle &angle);
    Angle operator+=(const Angle &angle);
    Angle operator-=(const Angle &angle);
    Angle operator*(const double &scalaire);
    bool operator==(Angle &a);
    bool presqueEgales(Angle &ang);
    Angle(const Angle &original);
    float getValueInRadian();
};


#endif // ANGLE_H_INCLUDED

