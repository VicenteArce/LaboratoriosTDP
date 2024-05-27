#include "Clique.h"

/*
    * Metodo: Constructor->Clique
    * Descripcion: Constructor de la clase Clique por defecto.
    * Parametros: Ninguno
    * Retorno: 
    *     - void.
*/
Clique::Clique(){
    this->adyacencyMatrix = vector<vector<int>>();
    this->size = -1;
}

/*
    * Metodo: Constructor->Clique
    * Descripcion: Constructor de la clase Clique con parametros.
    * Parametros:
    *   - adyacencyMatrix: Matriz de adyacencia del grafo.
    *   - size: Tamaño del grafo.
    * Retorno:
    *    - void.
*/
Clique::Clique(vector<vector<int>> adyacencyMatrix, int size){
    this->adyacencyMatrix = adyacencyMatrix;
    this->size = size;
}

/*
    * Metodo: Destructor->Clique
    * Descripcion: Destructor de la clase Clique.
    * Parametros: Ninguno
    * Retorno:
    *    - void.
*/
Clique::~Clique(){
    this->adyacencyMatrix.clear();
}

/*
    * Metodo: getAdyacencyMatrix
    * Descripcion: Metodo que retorna la matriz de adyacencia del grafo.
    * Parametros: Ninguno
    * Retorno:
    *    - vector<vector<int>>: Matriz de adyacencia del grafo.

*/
vector<vector<int>> Clique::getAdyacencyMatrix(){
    return this->adyacencyMatrix;
}

/*
    * Metodo: getMaxClique
    * Descripcion: Metodo que retorna el clique máximo.
    * Parametros: Ninguno
    * Retorno:
    *    - set<int>: Clique máximo.
*/
set<int> Clique::getMaxClique(){
    return this->maxClique;
}

/*
    * Metodo: getSize
    * Descripcion: Metodo que retorna el tamaño del grafo.
    * Parametros: Ninguno
    * Retorno:
    *    - int: Tamaño del grafo.
*/
int Clique::getSize(){
    return this->size;
}

/*
    * Metodo: setAdyacencyMatrix
    * Descripcion: Metodo que establece la matriz de adyacencia del grafo.
    * Parametros:
    *   - adyacencyMatrix: Matriz de adyacencia del grafo.
    * Retorno:
    *    - void.
*/
void Clique::setAdyacencyMatrix(vector<vector<int>> adyacencyMatrix){
    this->adyacencyMatrix = adyacencyMatrix;
}

/*
    * Metodo: setSize
    * Descripcion: Metodo que establece el tamaño del grafo.
    * Parametros:
    *   - size: Tamaño del grafo.
    * Retorno:
    *    - void.
*/
void Clique::setSize(int size){
    this->size = size;
}

/*
    * Metodo: setMaxClique
    * Descripcion: Metodo que establece el clique máximo.
    * Parametros:
    *   - maxClique: Clique máximo.
    * Retorno:
    *    - void.
*/
void Clique::setMaxClique(set<int> maxClique){
    this->maxClique = maxClique;
}

/*
    * Metodo: bronKerbosch
    * Descripcion: Metodo que implementa el algoritmo de Bron-Kerbosch para encontrar el clique máximo.
    * Parametros:
    *   - R: Conjunto de vértices que forman el clique actual.
    *   - P: Conjunto de vértices que pueden ser añadidos al clique actual.
    *   - X: Conjunto de vértices que no pueden ser añadidos al clique actual.
    * Retorno:
    *   - void.
*/
void Clique::bronKerbosch(set<int> *R, set<int> *P, set<int> *X){
    if(P->empty() && X->empty()){           // Si P y X están vacíos, hemos encontrado un clique
        if(R->size() > this->maxClique.size()){   // Si el clique actual es mayor que el clique máximo, lo actualizamos
            this->maxClique = *R;
        }
        return;
    }
    int pivot = this->getOptimalPivot(P, X);    // Seleccionamos el vértice con mayor cantidad de vecinos en P y X
    set<int> *Pcopy = new set<int>(*P);         
    for(int vertex : *P){
        if(this->adyacencyMatrix[pivot][vertex] == 1){     
            continue;
        }
        set<int> *Rcopy = new set<int>(*R);
        Rcopy->insert(vertex);
        set<int> *Pnew = new set<int>();
        set<int> *Xnew = new set<int>();
        for(int neighbor : *P){
            if(this->adyacencyMatrix[vertex][neighbor] == 1){
                Pnew->insert(neighbor);
            }
        }
        for(int neighbor : *X){
            if(this->adyacencyMatrix[vertex][neighbor] == 1){   
                Xnew->insert(neighbor);
            }
        }
        
        if(Rcopy->size() + Pnew->size() > this->maxClique.size()){  // Si el clique actual es mayor que el clique máximo, seguimos explorando
            bronKerbosch(Rcopy, Pnew, Xnew);
        }

        if(Pcopy->find(vertex) != Pcopy->end()){  // Eliminamos el vértice de P y lo añadimos a X
            Pcopy->erase(vertex);
            X->insert(vertex);
        }
        delete Rcopy;
        delete Pnew;
        delete Xnew;
        
    }
    delete Pcopy;
    
}


/*
    * Metodo: neighbors
    * Descripcion: Metodo que retorna los vecinos de un vértice.
    * Parametros:
    *   - vertex: Vértice del cual se quieren obtener los vecinos.
    * Retorno:
    *   - set<int>*: Conjunto de vecinos del vértice.
*/
set<int>* Clique::neighbors(int vertex){
    set<int> *neighbors = new set<int>();
    for(int i = 0; i < this->size; i++){
        if(this->adyacencyMatrix[vertex][i] == 1){
            neighbors->insert(i);
        }
    }
    return neighbors;
}

/*
    * Metodo: getOptimalPivot
    * Descripcion: Metodo que retorna el vértice con mayor cantidad de vecinos en P.
    * Parametros:
    *   - P: Conjunto de vértices que pueden ser añadidos al clique actual.
    *   - X: Conjunto de vértices que no pueden ser añadidos al clique actual.
*/
int Clique::getOptimalPivot(set<int> *P, set<int> *X){
    int pivot = -1;
    int maxNeighbors = -1;
    
    for(int vertex : *P){
        int neighbors = 0;
        for(int neighbor : *P){
            if(this->adyacencyMatrix[vertex][neighbor] == 1){
                neighbors++;
            }
        }
        if(neighbors > maxNeighbors){
            maxNeighbors = neighbors;
            pivot = vertex;
        }
    }

    for(int vertex : *X){
        int neighbors = 0;
        for(int neighbor : *P){
            if(this->adyacencyMatrix[vertex][neighbor] == 1){
                neighbors++;
            }
        }
        if(neighbors > maxNeighbors){
            maxNeighbors = neighbors;
            pivot = vertex;
        }
    }
    return pivot;
}


/*
    * Metodo: readArchive
    * Descripcion: Metodo que lee un archivo con la información de un grafo y lo almacena en la matriz de adyacencia.
    * Parametros: Ninguno
    * Retorno: 
    *    - void.
*/
void Clique::readArchive(){
    string filename;
    ifstream file;
    bool fileExists = false;

    while (!fileExists){
        cout << "Introduza el nombre del archivo: ";
        cin >> filename;
        file.open(filename, ios::in);
        if(file){
            fileExists = true;
        }
        else {
            cout << "Archivo no encontrado, por favor ingresa un nombre de archivo correcto." << endl;
        }
    }
    if(file.is_open()){
        string line;
        getline(file, line);
        this->size = stoi(line);
        this->adyacencyMatrix = vector<vector<int>>(this->size, vector<int>(this->size, 0));
        while(getline(file, line)){
            istringstream iss(line);
            int vertex, neighbor;
            iss >> vertex >> neighbor;
            this->adyacencyMatrix[vertex][neighbor] = 1;
            this->adyacencyMatrix[neighbor][vertex] = 1;
        }
    }
    printMatrix();
    file.close();
}


/*
    * Metodo: printMatrix
    * Descripcion: Metodo que imprime la matriz de adyacencia del grafo.
    * Parametros: Ninguno
    * Retorno:
    *    - void.
*/
void Clique::printMatrix(){
    for(int i = 0; i < this->size; i++){
        for(int j = 0; j < this->size; j++){
            cout << this->adyacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

