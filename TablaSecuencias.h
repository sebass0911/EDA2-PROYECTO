//Responsable: Sebastian
//  promps de IA usados en este archivo:


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DNASequence.h"
using namespace std;

class TablaSecuencias {
private:
    vector<DNASequence> tabla;
    vector<bool> ocupado;
    int m;                       // numero de bins
    int n;                       // numero de secuencias guardadas


    int hashFunction(const string& id);

    // true si x es primo
    bool esPrimo(int x);

    int siguientePrimo(int x);

    void colocar(const DNASequence& s);

    void rehash();

public:
    TablaSecuencias() {
        m = 10;
        n = 0;
        tabla.resize(m);
        ocupado.assign(m, false);
    }

    // Inserta una secuencia
    bool insertar(const DNASequence& s);

    // Busca por ID, devuelve nullptr si no esta
    DNASequence* buscar(const string& id);
};
