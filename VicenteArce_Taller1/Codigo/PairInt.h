#include <iostream>

using namespace std;

class PairInt{
    public:
        int first;  // Primer elemento
        int second; // Segundo elemento

        PairInt();  // Constructor por defecto
        PairInt(int first, int second); // Constructor con parametros
        int getFirst(); // Obtener primer elemento
        int getSecond();    // Obtener segundo elemento
        
};