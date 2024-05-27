#ifndef Menu_h
#define Menu_h

#include <iostream>
#include "Clique.h"

using namespace std;

/*
    * Clase Menu
    * Esta clase es usada para mostrar y manejar la logica del menú principal del programa.
    * La clase Menu es representada por un constructor y dos métodos.
    * ejecutarAlgoritmo: Método que ejecuta el algoritmo de Bron-Kerbosch.
    * menu: Método que muestra y maneja la logica del menú principal del programa.
*/
class Menu{
    public:
        // Constructor
        Menu();

        void ejecutarAlgoritmo(Clique *clique); 
        void menu();
};

#endif // Menu_h