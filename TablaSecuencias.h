//Responsable: Sebastian
//  prompts de IA usados en este archivo

// 1."Elabora el esqueleto de TablaSecuencias.h para una tabla hash con linear
// probing que guarde secuencias de ADN. Define los atributos, el constructor con m = 10 y funciones
// (funcion hash, primo, sigprimo, colocar, rehash, insertar y buscar),sin implementa codigo.

//2. "Revisa mi avance de TablaSecuencias. No me des el codigo corregido, solo dime que esta bien, que falta y que podria fallar."

//3. "ubica posibles errores de mi TablaSecuencias.h y senalame en que linea estaba, cada uno y por que era un error."

#ifndef TABLASECUENCIAS_H
#define TABLASECUENCIAS_H

#include <iostream>
#include <string>
#include "DNASequence.h"
#include <vector>
using namespace std;

class TablaSecuencias {
private:
    vector<DNASequence> tabla;
    int m;                       // numero de bins
    int n;                       // numero de secuencias guardadas
    int sondeos;
    int numRehash;


    int hashFunction(const string& id) {
        int h = 0;
        for (size_t i = 0; i < id.length(); i++) {
            h = (h * 31 + id[i]) % m;
        }
        return h;
    }

    // true si x es primo
    bool esPrimo(int x) {
        if (x < 2) return false;
        for (int d = 2; d * d <= x; d++) {
            if (x % d == 0) return false;
        }
        return true;
    }

    int siguientePrimo(int x) {
        while (!esPrimo(x)) x++;
        return x;
    }


    //  cuantos bins reviso
    int colocar(const DNASequence& s) {
        int i = hashFunction(s.id);
        int revisados = 1;
        while (tabla[i].id != "") {
            i = (i + 1) % m;
            revisados++;
        }
        tabla[i] = s;
        n++;
        return revisados;
    }

    void rehash() {
        vector<DNASequence> viejaTabla = tabla;
        int viejoM = m;

        m = siguientePrimo(2 * n);
        tabla = vector<DNASequence>(m);
        n = 0;

        for (int i = 0; i < viejoM; i++) {
            if (viejaTabla[i].id != "") colocar(viejaTabla[i]);
        }
        numRehash++;

        if (verbose) {
            cout << "  [rehash] " << viejoM << " -> " << m << " bins (alfa = "
                 << factorCarga() << ")" << endl;
        }
    }

public:
    bool verbose;
    TablaSecuencias() {
        m = 10;
        n = 0;
        sondeos = 0;
        numRehash = 0;
        verbose = false;
        tabla = vector<DNASequence>(m);
    }

    bool insertar(const DNASequence& s) {
        if (buscar(s.id) != nullptr) return false;

        if (n + 1 > m) rehash();

        sondeos += colocar(s);
        return true;
    }

//busqueda x id
    DNASequence* buscar(const string& id) {
        int i = hashFunction(id);
        for (int revisados = 0; revisados < m; revisados++) {
            if (tabla[i].id == "") return nullptr;
            if (tabla[i].id == id) return &tabla[i];
            i = (i + 1) % m;
        }
        return nullptr;
    }

    int tamano() { return m; }
    int cantidad() { return n; }
    double factorCarga() { return (double)n / m; }
    int totalSondeos() { return sondeos; }
    int totalRehash() { return numRehash; }

    double promedioSondeosInsercion() {
        if (n == 0) return 0;
        return (double)sondeos / n;
    }

    double promedioSondeosBusqueda() {
        if (n == 0) return 0;
        int total = 0;
        for (int j = 0; j < m; j++) {
            if (tabla[j].id == "") continue;
            int i = hashFunction(tabla[j].id);
            int revisados = 1;
            while (i != j) {
                i = (i + 1) % m;
                revisados++;
            }
            total += revisados;
        }
        return (double)total / n;
    }

    void mostrarEstado() {
        cout << "Tabla 1 (linear probing)" << endl;
        cout << "  bins: " << m << " | secuencias: " << n
             << " | factor de carga: " << factorCarga()
             << " | rehash: " << numRehash << endl;
        cout << "  sondeos promedio al insertar: " << promedioSondeosInsercion() << endl;
        cout << "  sondeos promedio al buscar:   " << promedioSondeosBusqueda() << endl;
    }

    void mostrarTabla() {
        for (int i = 0; i < m; i++) {
            if (tabla[i].id != "") {
                cout << "Bin " << i << ": " << tabla[i].id
                     << " (" << tabla[i].sequence.length() << " nt)" << endl;
            }
        }
    }
};

#endif
