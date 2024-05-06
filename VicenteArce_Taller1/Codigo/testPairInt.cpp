#include "PairInt.h"

int main(){
    PairInt *pair = new PairInt(1, 2); // Creiamos un par de enteros
    cout <<"(" <<pair->first << "," << pair->second << ")" << endl; // Imprimimos el par de enteros
    return 0;
}