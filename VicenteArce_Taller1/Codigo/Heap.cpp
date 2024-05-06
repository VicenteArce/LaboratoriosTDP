#include "Heap.h"

// Constructor con parametros
Heap::Heap(int maxSize)
{
    this->maxSize = maxSize;
    this->size = 0;
    this->heap = new State *[maxSize];
}

// Destructor
Heap::~Heap()
{
    for (int i = 0; i < this->size; i++)
    {
        delete this->heap[i];
    }
    delete[] this->heap;
}

// Insertar
void Heap::push(State *state)
{
    if (this->size == this->maxSize)
    {
        State **temp = new State *[this->maxSize * 2];
        for (int i = 0; i < this->size; i++)
        {
            temp[i] = this->heap[i];
        }
        delete[] this->heap;
        this->heap = temp;
        this->maxSize = 2 * this->maxSize;
    }
    this->heap[this->size] = state;
    this->bubbleUp(this->size);
    this->size++;
}

// Eliminar
State *Heap::pop()
{
    if (this->size == 0)
    {
        return nullptr;
    }
    State *state = this->heap[0];
    this->heap[0] = this->heap[this->size - 1];
    this->size--;
    this->heapify(0);
    return state;
}

// Verificar si esta vacio
bool Heap::isEmpty()
{
    return this->size == 0;
}

// Subir
void Heap::bubbleUp(int index)
{
    int parent = (index - 1) / 2;
    if (index > 0 && this->heap[index]->weight < this->heap[parent]->weight)
    {
        this->swap(index, parent);
        this->bubbleUp(parent);
    }
}

// Heapify
void Heap::heapify(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    if (left < this->size && this->heap[left]->weight < this->heap[smallest]->weight)
    {
        smallest = left;
    }
    if (right < this->size && this->heap[right]->weight < this->heap[smallest]->weight)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        this->swap(index, smallest);
        this->heapify(smallest);
    }
}

// Intercambiar
void Heap::swap(int index1, int index2)
{
    State *temp = this->heap[index1];
    this->heap[index1] = this->heap[index2];
    this->heap[index2] = temp;
}
// Comparar si son iguales
bool Heap::equal(State *state1, State *state2)
{
    for (int i = 0; i < state1->numRows; i++)
    {
        for (int j = 0; j < state1->numCols; j++)
        {
            if (state1->board[i][j] != state2->board[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

// Verificar si contiene un estado y reemplazar por un estado si tiene una menor profundidad
bool Heap::Contains(Heap *a,State *state)
{
    for (int i = 0; i < this->size; i++){
        if (this->equal(this->heap[i], state)){
            if (this->heap[i]->depth > state->depth){
                this->heap[i]->depth = state->depth;
                this->heap[i]->weight = state->weight;
                return true;
            }
            return true;
        }
    }
    return false;
}

// Expandir nodos
Heap Heap::expand()
{
    Heap newHeap(this->maxSize * 2);
    for (int i = 0; i < this->size; i++)
    {
        newHeap.push(this->heap[i]);
    }
    return newHeap;
}