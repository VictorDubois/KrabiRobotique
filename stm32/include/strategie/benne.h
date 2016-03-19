#ifndef BENNE_H
#define BENNE_H

class Benne
{
public:
    Benne();

    ~Benne();

    void setIsBenneEmpty();
    void setIsBenneFull();

    bool getIsBenneEmpty();
    bool getIsBenneFull();

protected:
    bool isBenneEmpty;
};

#endif // BENNE_H
