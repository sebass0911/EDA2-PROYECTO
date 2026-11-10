//Responsable: Alessandro
//Prompts de IA usados en este archivo (obligatorio segun el enunciado):

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <string>
#include <vector>
#include "TablaKmers.h"
using namespace std;

class MaxHeap {
private:
    vector<KmerConteo> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    void heapifyUp(int i) {
        // TODO (Alessandro)
    }

    void heapifyDown(int i) {
        // TODO (Alessandro)
    }

public:

    void construir(const vector<KmerConteo>& datos) {
        // TODO (Alessandro)
    }

    // Inserta un k-mer con su conteo  -> O(log N)
    void insertar(const KmerConteo& kc) {
        // TODO (Alessandro)
    }

    KmerConteo extraerMax() {
        KmerConteo maximo;
        maximo.kmer = "";
        maximo.conteo = 0;
        // TODO (Alessandro)
        return maximo;
    }

    bool vacio() { return heap.empty(); }
    int tamano() { return (int)heap.size(); }
};

void topN(const vector<KmerConteo>& conteos, int n) {
    // TODO (Alessandro):
    //  1. Construir el heap con conteos
    //  2. Llamar n veces a extraerMax() e imprimir cada resultado.
    //  3. Cuidar el caso en que n sea mayor que la cantidad de k-mers.
}

#endif
