#ifndef ASTARALGORITHM_H
#define ASTARALGORITHM_H

#include <iostream>
#include "Heap.h"

class AStarAlgorithm {
    public:
        State *initialState;    // Estado inicial
        Heap *open;             // Heap de estados abiertos
        Heap *closed;           // Heap de estados cerrados

        AStarAlgorithm();       // Constructor por defecto
        AStarAlgorithm(State* initialState);        // Constructor con parametros

        State *AStar(float pMT, float pMDLC, float pD);     // Algoritmo A*
};

#endif