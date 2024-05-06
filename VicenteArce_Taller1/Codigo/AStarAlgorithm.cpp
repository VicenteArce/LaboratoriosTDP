#include "AStarAlgorithm.h"

using namespace std;

// Constructor por defecto
AStarAlgorithm::AStarAlgorithm()
{
    this->initialState = nullptr;
    this->open = new Heap(1000);
    this->closed = new Heap(1000);
}

// Constructor con parametros
AStarAlgorithm::AStarAlgorithm(State *initialState)
{
    this->initialState = initialState;
    this->open = new Heap(1000);
    this->closed = new Heap(1000);
}

// Algoritmo A*
State *AStarAlgorithm::AStar(float pMT, float pMDLC, float pD){
    // Inicializamos el peso del estado inicial
    this->initialState->weight = pMT * this->initialState->heuristicMisplacedTiles() + pMDLC * this->initialState->heuristicManhattanDistanceAndLinearConflict() + pD * this->initialState->depth;
    this->open->push(this->initialState);   // Insertamos el estado inicial en la lista de abiertos
    while (!this->open->isEmpty()){
        State *currentState = open->pop();  // Sacamos el estado con menor peso del heap de abiertos
        if (currentState->isFinalState())   // Verificamos si es el estado final
        {
            return currentState;    // Retornamos el estado si es la solucion
        }
        this->closed->push(currentState);   // Insertamos el estado en la lista de cerrados
        State **children = currentState->expand();  // Expandimos los nodos
        for (int i = 0; i < 4; i++)
        {
            State *child = children[i]; // Obtenemos el hijo i-esimo
            if (child == nullptr)    // Verificamos si es nulo, si lo es, simplemente continuamos   
            {
                continue;
            }
            if (!this->closed->Contains(this->closed,child)) // Verificamos si el hijo no esta en la lista de cerrados (Para no crear bucles)
            {
                if (!this->open->Contains(this->open,child))   // Verificamos si el hijo no esta en la lista de abiertos (Para no crear bucles))
                {
                    if(child->depth > 70 && this->initialState->numCols > 4){
                        pD = 0.15;   // Cambiamos el peso de la profundidad si la profundidad del hijo es mayor a 70, esto para favorecer el tiempo a casos mas complejos.
                    }
                    child->weight = pMT * child->heuristicMisplacedTiles() + pMDLC * child->heuristicManhattanDistanceAndLinearConflict() + pD * child->depth;  // Calculamos el peso del hijo
                    this->open->push(child);    // Insertamos el hijo en la lista de abiertos
                }
                else
                {
                    delete child;   // Eliminamos el hijo si ya esta en la lista de abiertos
                }
            }
            else
            {
                delete child;   // Eliminamos el hijo si ya esta en la lista de cerrados
            }
        }
    }

    return nullptr; // Retornamos nulo si no se encontro solucion 
}