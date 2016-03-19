#include "benne.h"

Benne::Benne()
{
    isBenneEmpty = true;
}

void Benne::setBenneEmpty() {
    isBenneEmpty = true;
}

void Benne::setBenneFull() {
    isBenneEmpty = false;
}

bool Benne::getIsBenneEmpty() {
    return isBenneEmpty;
}

bool Benne::getIsBenneFull() {
    return !isBenneEmpty;
}
