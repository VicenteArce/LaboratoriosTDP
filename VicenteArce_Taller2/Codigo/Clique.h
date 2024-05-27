#ifndef Clique_h
#define Clique_h

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <sstream>
#include <fstream>

using namespace std;

/*
    * Clase Clique:
    * Esta clase es usada para, dado un grafo no dirigido, encontrar un clique máximo.
    * La clase Clique es representada por una matriz de adyacencia del grafo, un conjunto
    * de vértices que representan el clique máximo y el tamaño del grafo.
*/

class Clique {
    private:
        vector<vector<int>> adyacencyMatrix;
        set<int> maxClique;
        int size;
        
    public:
        // Constructor
        Clique();
        Clique(vector<vector<int>> adyacencyMatrix, int size);

        // Destructor
        ~Clique();

        // Getters
        vector<vector<int>> getAdyacencyMatrix();
        set<int> getMaxClique();
        int getSize();

        // Setters
        void setAdyacencyMatrix(vector<vector<int>> adyacencyMatrix);
        void setMaxClique(set<int> maxClique);
        void setSize(int size);
        

        // Bron-Kerbosch algorithm
        void bronKerbosch(set<int> *R, set<int> *P, set<int> *X);
        set<int>* neighbors(int vertex);

        // GetOptimalPivot
        int getOptimalPivot(set<int> *P, set<int> *X);

        // ReadArchive
        void readArchive();
        void printMatrix();

        
};

#endif /* Clique_h */

