//  Prompts de IA usados en este archivo:
#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

const string NUCLEOTIDOS = "ACGT";


int indice2mer(const string& par) {
    // TODO (Alessandro)
    return -1;
}

void grafoKmers(const string& secuencia, double beta) {
    double matriz[16][16];   // todo empieza en 0
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            matriz[i][j] = 0;
        }
    }

    // TODO (Alessandro):
    //  1. Cortar la secuencia en pares sin solaparse.
    //  2. Doble for (i < j) sumando 1 / pow(j - i, beta) en matriz[fila][columna].
    //  3. Imprimir la matriz con los nombres de los 2-mers (separar columnas con "\t").
}

#endif
