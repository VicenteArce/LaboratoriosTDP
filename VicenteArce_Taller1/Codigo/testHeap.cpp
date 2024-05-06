#include "Heap.h"


int main(){
    // Creamos un heap
    Heap *heap = new Heap(10);

    // Creamos un estado
    State *state = new State();
    state->readMatrix(); // Leemos la matriz desde un archivo de texto
    State **children = state->expand(); // Expandimos el estado creando sus hijos

    // Insertamos el estado en el heap
    heap->push(state);


    // Insertamos los hijos en el heap calculando su peso si el estado no es nulo    
    for (int i = 0; i < 4; i++)
    {
        if (children[i] == nullptr)
        {
            continue;
        }
        children[i]->weight = children[i]->heuristicMisplacedTiles() + children[i]->heuristicManhattanDistanceAndLinearConflict();
        heap->push(children[i]); // Insertamos los hijos en el heap
    }

    State *a = heap->pop(); // Sacamos el estado con menor peso
    a->printBoard(); // Imprimimos el tablero con menor peso de los que estan en el heap

    return 0;
}