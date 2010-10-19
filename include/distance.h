#ifndef DISTANCE_H_INCLUDED
#define DISTANCE_H_INCLUDED

class Distance{
    private:
    float value;

    public:
    float getValueInMillimeters() const;
    Distance();
    Distance(float distance_en_millimetres);
    Distance operator+(const Distance &dist);
    Distance operator-(const Distance &dist);
    Distance operator-() const;
    Distance operator*(const Distance &dist);
    Distance operator*(float dist);
    Distance operator=(const Distance &dist);
    Distance operator+=(const Distance &dist);
    Distance operator-=(const Distance &dist);
    bool operator==(const Distance &d);
    bool presqueEgales(const Distance &d);
    bool operator>(const Distance &dist);
    bool operator<(const Distance &dist);
};

#endif // DISTANCE_H_INCLUDED
