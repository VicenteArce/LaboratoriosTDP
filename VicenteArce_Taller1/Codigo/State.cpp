#include <iostream>
#include <sstream>
#include <fstream>
#include "State.h"

using namespace std;

// Constructor de State
State::State()
{
    this->board = nullptr;
    this->finalBoard = nullptr;
    this->numRows = 0;
    this->numCols = 0;
    this->weight = 0;
    this->depth = 0;
    this->zeroPosition = PairInt(0, 0);
    this->parent = nullptr;
}

// Constructor de State
State::State(int numRows, int numCols, int **board, int weight, int depth, PairInt zeroPosition, State *parent)
{
    this->numRows = numRows;
    this->numCols = numCols;
    this->board = board;
    this->finalBoard = generateFinalBoard(numRows);
    this->weight = weight;
    this->depth = depth;
    this->zeroPosition = zeroPosition;
    this->parent = parent;
}

// Destructor de State
State::~State()
{
    for (int i = 0; i < this->numRows; i++)
    {
        delete[] this->board[i];
        delete[] this->finalBoard[i];
    }
    delete[] this->board;
    delete[] this->finalBoard;
}

// Imprimir tablero
void State::printBoard()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// imprimir camino de solucion
void State::printSolution()
{
    if (parent != nullptr)
    {

        parent->printSolution();
    }
    printBoard();
    cout << endl;
}

// contar pasos
int State::countSteps()
{
    if (parent != nullptr)
    {
        return 1 + parent->countSteps();
    }
    return 0;
}

// Generar tablero final
int **State::generateFinalBoard(int dimension)
{
    int **finalBoard = new int *[numRows];
    int counter = 1;
    for (int i = 0; i < dimension; i++)
    {
        finalBoard[i] = new int[numCols];
        for (int j = 0; j < dimension; j++)
        {
            finalBoard[i][j] = counter;
            counter++;
        }
    }

    finalBoard[numRows - 1][numCols - 1] = 0;
    return finalBoard;
}

// Intercambiar posiciones
int **State::swap(int x1, int y1, int x2, int y2)
{
    int **newBoard = new int *[numRows];
    for (int i = 0; i < numRows; i++)
    {
        newBoard[i] = new int[numCols];
        for (int j = 0; j < numCols; j++)
        {
            newBoard[i][j] = board[i][j];
        }
    }
    int temp = newBoard[x1][y1];
    newBoard[x1][y1] = newBoard[x2][y2];
    newBoard[x2][y2] = temp;
    return newBoard;
}

// Obtener coordenadas
PairInt State::getCoorinates(int num)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (board[i][j] == num)
            {
                return PairInt(i, j);
            }
        }
    }
    return PairInt(-1, -1);
}

// Obtener coordenadas de la posicion final
PairInt State::getFinalPositionCoordinates(int num)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (finalBoard[i][j] == num)
            {
                return PairInt(i, j);
            }
        }
    }
    return PairInt(-1, -1);
}

// Movimientos
State *State::moveUp()
{
    if (zeroPosition.first == 0)
    {
        return nullptr;
    }
    else
    {
        return new State(numRows, numCols, swap(zeroPosition.first, zeroPosition.second, zeroPosition.first - 1, zeroPosition.second), weight + 1, depth + 1, PairInt(zeroPosition.first - 1, zeroPosition.second), this);
    }
}


State *State::moveDown()
{
    if (zeroPosition.first == numRows - 1)
    {
        return nullptr;
    }
    else
    {
        return new State(numRows, numCols, swap(zeroPosition.first, zeroPosition.second, zeroPosition.first + 1, zeroPosition.second), weight + 1,depth + 1, PairInt(zeroPosition.first + 1, zeroPosition.second), this);
    }
}

State *State::moveLeft()
{
    if (zeroPosition.second == 0)
    {
        return nullptr;
    }
    else
    {
        return new State(numRows, numCols, swap(zeroPosition.first, zeroPosition.second, zeroPosition.first, zeroPosition.second - 1), weight + 1, depth + 1, PairInt(zeroPosition.first, zeroPosition.second - 1), this);
    }
}

State *State::moveRight()
{
    if (zeroPosition.second == numCols - 1)
    {
        return nullptr;
    }
    else
    {
        return new State(numRows, numCols, swap(zeroPosition.first, zeroPosition.second, zeroPosition.first, zeroPosition.second + 1), weight + 1, depth + 1, PairInt(zeroPosition.first, zeroPosition.second + 1), this);
    }
}

// Expandir nodos
State **State::expand()
{
    State **children = new State *[4];
    children[0] = moveUp();
    children[1] = moveDown();
    children[2] = moveLeft();
    children[3] = moveRight();
    return children;
}

// Tablero a arreglo
int *State::boardToArray()
{
    int *array = new int[numRows * numCols];
    int counter = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            array[counter] = board[i][j];
            counter++;
        }
    }
    return array;
}

// Leer matriz desde un archivo de texto

// Método usado para contar el número de números en una línea
//(En este caso para contar los números que hay en la primera fila de la matriz)
int State::contarNumerosEnLinea(const string &linea)
{
    istringstream iss(linea);
    int contador = 0;
    int valor;

    while (iss >> valor)
    {
        contador++;
    }
    return contador;
}

// Método para leer la matriz desde un archivo de texto
void State::readMatrix()
{
    string fileName;
    ifstream file;
    bool fileExists = false;

    while (!fileExists)
    {
        cout << "Introduza el nombre del archivo: ";
        cin >> fileName;

        file.open(fileName, ios::in);

        if (file)
        {
            fileExists = true;
        }
        else
        {
            cout << "Archivo no encontrado, por favor ingresa un nombre de archivo correcto." << endl;
        }
    }

    string line;
    getline(file, line);
    int contador = contarNumerosEnLinea(line);
    int **matrix = new int *[contador];

    for (int i = 0; i < contador; i++)
    {
        matrix[i] = new int[contador];
        istringstream iss(line);
        int valor;
        int j = 0;
        while (iss >> valor)
        {
            matrix[i][j] = valor;
            j++;
        }
        getline(file, line);
    }

    board = matrix;
    numRows = contador;
    numCols = contador;
    finalBoard = generateFinalBoard(contador);
    zeroPosition = getCoorinates(0);
    weight = heuristicManhattanDistanceAndLinearConflict() + heuristicMisplacedTiles(); // PLACEHOLDER
    parent = nullptr;                                                  // PLACEHOLDER

    file.close();
}

// Ordenar arreglo
int *State::sort(int *arr, int n)
{
    int *sortedArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        sortedArr[i] = arr[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (sortedArr[j] > sortedArr[j + 1])
            {
                int temp = sortedArr[j];
                sortedArr[j] = sortedArr[j + 1];
                sortedArr[j + 1] = temp;
            }
        }
    }
    return sortedArr;
}

// Verificar si es un tablero valido
bool State::isValidBoard(){
    int *array = boardToArray();
    int *sortedArray = sort(array, numRows * numCols);
    for (int i = 0; i < numRows * numCols; i++){
        if (sortedArray[i] != i){
            return false;
        }
    }
    return true;
} 


// Heuristicas
int State::manhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int State::heuristicMisplacedTiles()
{
    int counter = 0;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (board[i][j] != finalBoard[i][j])
            {
                counter++;
            }
        }
    }
    return counter;
}

int State::heuristicManhattanDistanceAndLinearConflict()
{
    int counter = 0;
    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            int value = board[i][j];
            if (value != 0){
                PairInt finalPosition = getFinalPositionCoordinates(value);
                int finalRow = finalPosition.first;
                int finalCol = finalPosition.second;
                int manhattanDist = manhattanDistance(i, j, finalRow, finalCol);
                counter += manhattanDist;
                if (i == finalRow){
                    for (int k = j + 1; k < numCols; k++){
                        int nextValue = board[i][k];
                        if (nextValue != 0 && getFinalPositionCoordinates(nextValue).first == finalRow && nextValue < value){
                            counter += 2;
                        }
                    }
                }
                if (j == finalCol){
                    for (int k = i + 1; k < numRows; k++){
                        int nextValue = board[k][j];
                        if (nextValue != 0 && getFinalPositionCoordinates(nextValue).second == finalCol && nextValue < value){
                            counter += 2;
                        }
                    }
                }
            }
        }
    }

    return counter;
}

// Solvabilidad
// Verificar si es impar
bool State::isOdd(int num)
{
    return num % 2 != 0;
}

// Verificar si es par
bool State::isEven(int num)
{
    return num % 2 == 0;
}

// Obtener fila de la posicion del cero desde abajo
int State::getRowZeroPositionFromBottom()
{
    return numRows - zeroPosition.first;
}

// Obtener inversiones
int State::getInversions()
{
    int counter = 0;
    int *array = boardToArray();
    for (int i = 0; i < numRows * numCols; i++)
    {
        for (int j = i + 1; j < numRows * numCols; j++)
        {
            if (array[i] > array[j] && array[i] != 0 && array[j] != 0)
            {
                counter++;
            }
        }
    }
    return counter;
}

// Verificar si es solucionable
bool State::isSolvable()
{
    int inversions = getInversions();
    int rowZeroPositionFromBottom = getRowZeroPositionFromBottom();

    if (isOdd(numRows) && isEven(inversions))
    {
        return true;
    }
    else if (isEven(numRows) && isEven(rowZeroPositionFromBottom) && isOdd(inversions))
    {
        return true;
    }
    else if (isEven(numRows) && isOdd(rowZeroPositionFromBottom) && isEven(inversions))
    {
        return true;
    }

    return false;
}

// Verificar si es el estado final
bool State::isFinalState()
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (board[i][j] != finalBoard[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
