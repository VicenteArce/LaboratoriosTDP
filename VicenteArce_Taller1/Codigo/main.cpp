#include <iostream>
#include <ctime>
#include <iostream>

#include "AStarAlgorithm.h"


using namespace std;

int main()
{
    State state;
    state.readMatrix(); // Leemos la matriz desde un archivo introducido por el usuario

    // Se comprueba que el tablero sea valido (Que tenga numeros del 0 al n*n-1 y que estos no se repitan)
    if(!state.isValidBoard()){
        cout << "El tablero no es valido, asegurate que el archivo de texto contenga números correctos" << endl;
        return 0;
    }

    if (state.isSolvable()) {
        float pMT = 0;      // Peso de la heuristica de fichas mal colocadas
        float pMDLC = 0;    // Peso de la heuristica de distancia de Manhattan y conflicto lineal
        float pD = 0;       // Peso de la profundidad
        
        // Pesos de las heuristicas si el numero de columnas es menor o igual a 3
        if (state.numCols <= 3){
            pMT = 0.5;
            pMDLC = 1.1;
            pD = 0.8;
        }
        // Pesos de las heuristicas si el numero de columnas es igual a 4 
        else if (state.numCols == 4){
            pMT = 0.5;
            pMDLC = 1.5;
            pD = 0.7;
        }
        // Pesos de las heuristicas si el numero de columnas es mayor a 4
        else{
            pMT = 0.4;
            pMDLC = 1.5;
            pD = 1;
        }
        clock_t start = clock();    // Iniciamos el reloj
        State *algorithm = AStarAlgorithm(&state).AStar(pMT, pMDLC, pD); // Algoritmo A* con los pesos de las heuristicas dados en relacion al tamaño del tablero
        double time = (double)(clock() - start) / CLOCKS_PER_SEC; // Tiempo de ejecucion
        algorithm->printSolution(); // Imprimimos la solucion           
        cout << "Pasos de la solucion: " << algorithm->countSteps() << endl;    // Imprimimos los pasos de la solucion
        cout << "Tiempo de ejecucion: " << time << " segundos" << endl;   // Imprimimos el tiempo de ejecucion
    }
    else
    {
        cout << "No tiene solucion" << endl;    // No tiene solucion
    }

    return 0;
}