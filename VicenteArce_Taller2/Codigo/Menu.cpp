#include <iostream>
#include "Menu.h"
using namespace std;

/*
    * Metodo: Constructor->Menu
    * Descripcion: Constructor de la clase Menu por defecto.
    * Parametros: Ninguno
    * Retorno: 
    *     - void.

*/
Menu::Menu(){
}

/*
    * Metodo: ejecutarAlgoritmo
    * Descripcion: Metodo que ejecuta el algoritmo de Bron-Kerbosch. Encargandose de 
    *              inicializar los conjuntos R, P y Xy de calcular el tiempo de ejecución.
    * Parametros:
    *   - clique: Objeto de la clase Clique.
    * Retorno:
    *    - void.
*/
void Menu::ejecutarAlgoritmo(Clique *clique){
    set<int> *R = new set<int>();
    set<int> *P = new set<int>();
    set<int> *X = new set<int>();
    for(int i = 0; i < clique->getSize(); i++){
        P->insert(i);
    }
    clock_t start = clock();    // Iniciamos el reloj
    clique->bronKerbosch(R, P, X);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC; // Tiempo de ejecucion
    cout << "Clique maximo: {";
    for(int vertex : clique->getMaxClique()){
        if(vertex == *clique->getMaxClique().rbegin())
            cout << vertex;
        else
            cout << vertex << ", ";
    }
    cout << "}" << endl;
    cout << "Tamaño: " << clique->getMaxClique().size() << endl;
    cout << "Tiempo: " << time << " segundos" << endl;
    clique->~Clique();

}

/*
    * Metodo: menu
    * Descripcion: Metodo que muestra y maneja la logica del menú principal del programa.
    * Parametros: Ninguno
    * Retorno:
    *   - void. 
*/
void Menu::menu(){
    int option = 0;
    Clique *clique = nullptr;
    while (option != 2){
        cout << "\n##### Menu #####" << endl;
        cout << "1) Encontrar clique máximo" << endl;
        cout << "2) Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000000, '\n');
            option = 0; 
            cout << "Entrada no válida. Por favor, ingrese un número." << endl;
            continue; 
            }

        switch(option){
            case 1:
                clique = new Clique();
                clique->readArchive();
                ejecutarAlgoritmo(clique);
                break;
            case 2:
                cout << "Saliendo..." << endl;
                break;
            default:
                option = 0;
                cout << "Opción no válida" << endl;
                break;
        }   
    }
}