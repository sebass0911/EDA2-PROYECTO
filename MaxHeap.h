//Responsable: Alessandro
//Prompts de IA usados en este archivo (obligatorio segun el enunciado):

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class MaxHeap {
private:
    vector<pair<string, int>> heap;

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

    void construir(const vector<pair<string, int>>& datos) {
        // TODO (Alessandro)
    }

    // Inserta un par  -> O(log N)
    void insertar(const pair<string, int>& p) {
        // TODO (Alessandro)
    }

    pair<string, int> extraerMax() {
        // TODO (Alessandro)
        return make_pair("", 0);
    }

    bool vacio() { return heap.empty(); }
    int tamano() { return (int)heap.size(); }
};

void topN(const vector<pair<string, int>>& conteos, int n) {
    // TODO (Alessandro):
    //  1. Construir el heap con conteos
    //  2. Llamar n veces a extraerMax() e imprimir cada resultado.
    //  3. Cuidar el caso en que n sea mayor que la cantidad de k-mers.
}
