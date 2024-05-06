#include "AStarAlgorithm.h"

int main(){
    // Creamos un estado
    State state;
    state.readMatrix(); // Leemos la matriz desde un archivo de texto

    // Creamos un algoritmo A*
    AStarAlgorithm* aStar = new AStarAlgorithm(&state); // Use a pointer to AStarAlgorithm

    aStar->open->push(&state); // Push the address of the state to the open list
    aStar->open->pop()->printBoard(); // Pop the state from the open list
    return 0;
}   