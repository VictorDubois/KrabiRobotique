#include "benne.h"

Benne::Benne()
{
    isBenneEmpty = true;
}

void Benne::setIsBenneEmpty() {
    isBenneEmpty = true;
}

void Benne::setIsBenneFull() {
    isBenneEmpty = false;
}

bool Benne::getIsBenneEmpty() {
    return isBenneEmpty;
}

bool Benne::getIsBenneFull() {
    return !isBenneEmpty;
}
