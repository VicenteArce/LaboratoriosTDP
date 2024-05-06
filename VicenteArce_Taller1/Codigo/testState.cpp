#include "State.h"
#include <iostream>

int main()
{
    // Creamos un estado
    State *state = new State();
    state->readMatrix(); // Leemos la matriz desde un archivo de texto
    cout << "Initial state: " << endl;
    state->printBoard();           // Imprimimos el tablero
    PairInt zeroPosition = state->zeroPosition;
    cout << "Zero position: (" << zeroPosition.first + 1 << ", " << zeroPosition.second + 1<< ")" << endl; // Imprimimos la posicion del cero
    cout <<"------Childrens-------" << endl;
    State **children = state->expand(); // Expandimos el estado creando sus hijos
    if(children[0] == nullptr) cout << "\nChild 1 is null\n" << endl;
    else{
        cout << "Child 1: " << endl;
        children[0]->printBoard();
    }

    if(children[1] == nullptr) cout << "\nChild 2 is null\n" << endl;
    else{
        cout << "Child 2: " << endl;
        children[1]->printBoard();
    }

    if(children[2] == nullptr) cout << "\nChild 3 is null\n" << endl;
    else{
        cout << "Child 3: " << endl;
        children[2]->printBoard();
    }

    if(children[3] == nullptr) cout << "\nChild 4 is null\n" << endl;
    else{
        cout << "Child 4: " << endl;
        children[3]->printBoard();
    }
    
    
    return 0;
}