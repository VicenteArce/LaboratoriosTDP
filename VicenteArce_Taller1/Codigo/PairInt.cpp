#include "PairInt.h"

// Constructor por defecto
PairInt::PairInt()
{
    first = -1;
    second = -1;
}

// Constructor con parametros
PairInt::PairInt(int first, int second)
{
    this->first = first;
    this->second = second;
}

// Obtener primer elemento
int PairInt::getFirst()
{
    return first;
}

// Obtener segundo elemento
int PairInt::getSecond()
{
    return second;
}
