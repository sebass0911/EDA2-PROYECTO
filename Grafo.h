#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

const std::string NUCLEOTIDOS = "ACGT";

int indice2mer(const std::string& par) {
    if (par.size() != 2) return -1;
    int p0 = -1, p1 = -1;
    for (int i = 0; i < 4; i++) {
        if (NUCLEOTIDOS[i] == par[0]) p0 = i;
        if (NUCLEOTIDOS[i] == par[1]) p1 = i;
    }
    if (p0 == -1 || p1 == -1) return -1;
    return p0 * 4 + p1;
}

void grafoKmers(const std::string& secuencia, double beta) {
    int n = secuencia.size();

    std::vector<std::string> pares;
    std::vector<int> indices;
    for (int i = 0; i + 1 < n; i += 2) {
        std::string par = "";
        par = par + secuencia[i];
        par = par + secuencia[i + 1];
        int idx = indice2mer(par);
        if (idx != -1) {
            pares.push_back(par);
            indices.push_back(idx);
        }
    }

    double matriz[16][16];
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            matriz[i][j] = 0.0;
        }
    }

    int m = pares.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            int u = indices[i];
            int v = indices[j];
            double peso = 1.0 / std::pow((double)(j - i), beta);
            matriz[u][v] = matriz[u][v] + peso;
        }
    }

    std::string nombres[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::string s = "";
            s = s + NUCLEOTIDOS[i];
            s = s + NUCLEOTIDOS[j];
            nombres[i * 4 + j] = s;
        }
    }

    std::cout << "\t";
    for (int i = 0; i < 16; i++) {
        std::cout << nombres[i] << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < 16; i++) {
        std::cout << nombres[i] << "\t";
        for (int j = 0; j < 16; j++) {
            std::cout << matriz[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


#endif // GRAFO_H_INCLUDED
