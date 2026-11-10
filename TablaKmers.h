// Responsable: Sebastian
// Prompts de IA usados en este archivo (obligatorio segun el enunciado):
//

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

class TablaKmers {
private:
    vector<string> claves;
    vector<int> conteos;
    vector<bool> ocupado;
    int k;
    int m;
    int n;
    long long sondeos;

    int h1(const string& kmer) {
        // TODO (Sebastian)
        return 0;
    }

    int h2(const string& kmer) {
        // TODO (Sebastian)
        return 1;
    }

    bool esValido(const string& kmer) {
        // TODO (Sebastian)
        return true;
    }

public:
    TablaKmers(int tamK) {
        k = tamK;
        m = (int)pow(4, k);
        n = 0;
        sondeos = 0;
        claves.resize(m);
        conteos.assign(m, 0);
        ocupado.assign(m, false);
    }

    void insertar(const string& kmer) {
        // TODO (Sebastian)
    }

    int buscar(const string& kmer) {
        // TODO (Sebastian)
        return 0;
    }

    void contar(const string& secuencia) {
        // TODO (Sebastian)
    }

    vector<pair<string, int>> obtenerTodos() {
        vector<pair<string, int>> lista;
        // TODO (Sebastian)
        return lista;
    }

    int tamano() { return m; }
    int cantidad() { return n; }
    long long totalSondeos() { return sondeos; }

    void mostrar() {
        // TODO (Sebastian)
    }
};
