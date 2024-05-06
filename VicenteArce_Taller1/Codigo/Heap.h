#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include "State.h"

using namespace std;

class Heap{
    public:
        State **heap;   // Arreglo de estados
        int size;       // Tamaño
        int maxSize;    // Tamaño maximo

        Heap(int maxSize);  // Constructor con parametros
        ~Heap();            // Destructor
        void push(State *state);    // Insertar
        State *pop();       // Eliminar
        bool isEmpty();     // Verificar si esta vacio

        void bubbleUp(int index);           // Subir
        void heapify(int index);            // Heapify
        void swap(int index1, int index2);  // Intercambiar

        bool equal(State *state1, State *state2);   // Comparar si son iguales
        bool Contains(Heap *a,State *state);                // Verificar si contiene un estado

        Heap expand();      // Expandir nodos
};

#endif