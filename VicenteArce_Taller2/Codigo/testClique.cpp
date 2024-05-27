#include "Clique.h"

int main(){
    Clique c = Clique();
    c.readArchive();
    c.printMatrix();
    set<int> *R = new set<int>();
    set<int> *P = new set<int>();
    set<int> *X = new set<int>();
    for(int i = 0; i < c.getSize(); i++){
        P->insert(i);
    }
    clock_t start = clock();    // Iniciamos el reloj
    c.bronKerbosch(R, P, X);
    double time = (double)(clock() - start) / CLOCKS_PER_SEC; // Tiempo de ejecucion
    cout << "Clique maximo: {";
    for(int vertex : c.getMaxClique()){
        cout << vertex << ", ";
    }
    cout << "}" << endl;
    cout << "Tamaño: " << c.getMaxClique().size() << endl;
    cout << "Tiempo: " << time << " segundos" << endl;

    return 0;
}