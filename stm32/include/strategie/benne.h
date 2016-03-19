#ifndef BENNE_H
#define BENNE_H

class Benne
{
public:
    Benne();

    ~Benne();

    void setBenneEmpty();
    void setBenneFull();

    bool getIsBenneEmpty();
    bool getIsBenneFull();

protected:
    bool isBenneEmpty;
};

#endif // BENNE_H
