#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include "PairInt.h"

using namespace std;
class State {
public:
    // Atributos de State
    int **board;        // Tablero
    int **finalBoard;   // Tablero final
    int numRows;        // Numero de filas  
    int numCols;        // Numero de columnas
    int weight;         // Peso
    int depth;          // Profundidad
    PairInt zeroPosition;   // Posicion del cero
    State *parent;      // Padre
    State **children;   // Hijos

    State();    // Constructor por defecto    
    State(int numRows, int numCols, int **board, int weight, int depth, PairInt zeroPosition, State *parent);   // Constructor con parametros
    ~State();   // Destructor

    void printBoard();  // Imprimir tablero
    void printSolution();   // Imprimir camino de la solucion
    int countSteps();   // Contar pasos

    int **generateFinalBoard(int dimension);    // Generar tablero final
    int **swap(int x1, int y1, int x2, int y2);   // Intercambiar posiciones
    PairInt getCoorinates(int num);     // Obtener coordenadas
    PairInt getFinalPositionCoordinates(int num);   // Obtener coordenadas de la posicion final

    // Movimientos
    State *moveUp();    
    State *moveDown();
    State *moveLeft();
    State *moveRight();
    State **expand();   // Expandir nodos

    int *boardToArray();    // Tablero a arreglo    

    int contarNumerosEnLinea(const string &linea); // Contar numeros en linea
    void readMatrix();  // Leer matriz desde archivo
    int *sort(int *arr, int n); // Ordenar arreglo
    bool isValidBoard();    // Verificar si es un tablero valido

    // Heuristica
    int manhattanDistance(int x1, int y1, int x2, int y2);
    int heuristicMisplacedTiles();
    int heuristicManhattanDistanceAndLinearConflict();

    // Solvabilidad
    bool isOdd(int num);    // Verificar si es impar
    bool isEven(int num);   // Verificar si es par
    int getRowZeroPositionFromBottom(); // Obtener fila de la posicion del cero desde abajo
    int getInversions();    // Obtener inversiones
    bool isSolvable();      // Verificar si es solucionable

    // Verificar si es el estado final
    bool isFinalState();

};


#endif //STATE_H