// Responsable: Sebastian
// Prompts de IA usados en este archivo (obligatorio segun el enunciado):

// 1. "eevisa mi TablaKmers.h: verifica que h2 sea siempre impar y que la ventana saque bien los k-mers. Senalame los errores."

// 2. "Generame la funcion obtenerTodos() para pasar los k-mers al max-heap y explicame como funciona cada funcion."

#ifndef TABLAKMERS_H
#define TABLAKMERS_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

struct KmerConteo {
    string kmer;
    int conteo;
};

class TablaKmers {
private:
    vector<string> claves;
    vector<int> conteos;
    int k;
    int m;
    int n;
    int sondeos;
    int totalKmers;
    int saltados;
    bool doble;

    int h1(const string& kmer) {
        int h = 0;
        for (size_t i = 0; i < kmer.length(); i++) {
            h = (h * 31 + kmer[i]) % m;
        }
        return h;
    }

    int h2(const string& kmer) {
        if (!doble) return 1;
        int h = 0;
        for (size_t i = 0; i < kmer.length(); i++) {
            h = (h * 37 + kmer[i]) % m;
        }
        return 2 * (h % (m / 2)) + 1;
    }

    bool esValido(const string& kmer) {
        for (size_t i = 0; i < kmer.length(); i++) {
            char c = kmer[i];
            if (c != 'A' && c != 'C' && c != 'G' && c != 'T') return false;
        }
        return true;
    }

public:
    TablaKmers(int tamK, bool usarDobleHashing = true) {
        k = tamK;
        m = (int)pow(4, k);
        n = 0;
        sondeos = 0;
        totalKmers = 0;
        saltados = 0;
        doble = usarDobleHashing;
        claves = vector<string>(m, "");
        conteos = vector<int>(m, 0);
    }

    void insertar(const string& kmer) {
        int pos = h1(kmer);
        int salto = h2(kmer);
        for (int i = 0; i < m; i++) {
            sondeos++;
            if (conteos[pos] == 0) {
                claves[pos] = kmer;
                conteos[pos] = 1;
                n++;
                return;
            }
            if (claves[pos] == kmer) {
                conteos[pos]++;
                return;
            }
            pos = (pos + salto) % m;
        }
    }

    int buscar(const string& kmer) {
        int pos = h1(kmer);
        int salto = h2(kmer);
        for (int i = 0; i < m; i++) {
            if (conteos[pos] == 0) return 0;
            if (claves[pos] == kmer) return conteos[pos];
            pos = (pos + salto) % m;
        }
        return 0;
    }

    void contar(const string& secuencia) {
        int L = secuencia.length();
        for (int i = 0; i + k <= L; i++) {
            string kmer = secuencia.substr(i, k);
            if (esValido(kmer)) {
                insertar(kmer);
                totalKmers++;
            } else {
                saltados++;
            }
        }
    }

    vector<KmerConteo> obtenerTodos() {
        vector<KmerConteo> lista;
        for (int i = 0; i < m; i++) {
            if (conteos[i] > 0) {
                KmerConteo kc;
                kc.kmer = claves[i];
                kc.conteo = conteos[i];
                lista.push_back(kc);
            }
        }
        return lista;
    }

    int tamano() { return m; }
    int cantidad() { return n; }
    double factorCarga() { return (double)n / m; }
    int totalSondeos() { return sondeos; }
    int totalSaltados() { return saltados; }

    double promedioSondeosInsercion() {
        if (totalKmers == 0) return 0;
        return (double)sondeos / totalKmers;
    }

    double promedioSondeosBusqueda() {
        if (n == 0) return 0;
        int total = 0;
        for (int j = 0; j < m; j++) {
            if (conteos[j] == 0) continue;
            int pos = h1(claves[j]);
            int salto = h2(claves[j]);
            int revisados = 1;
            while (pos != j) {
                pos = (pos + salto) % m;
                revisados++;
            }
            total += revisados;
        }
        return (double)total / n;
    }

    void mostrarEstado() {
        cout << "Tabla 2 (" << (doble ? "double hashing" : "linear probing") << ", k = " << k << ")" << endl;
        cout << "  bins: " << m << " | k-mers distintos: " << n
             << " | factor de carga: " << factorCarga() << endl;
        cout << "  k-mers procesados: " << totalKmers << " | saltados: " << saltados << endl;
        cout << "  sondeos promedio al insertar: " << promedioSondeosInsercion() << endl;
        cout << "  sondeos promedio al buscar:   " << promedioSondeosBusqueda() << endl;
    }

    void mostrar() {
        for (int i = 0; i < m; i++) {
            if (conteos[i] > 0) {
                cout << "Bin " << i << ":\t" << claves[i] << " -> " << conteos[i] << endl;
            }
        }
    }
};

#endif
