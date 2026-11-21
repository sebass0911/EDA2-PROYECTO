// Responsable: Alessandro
// Prompts de IA usados en este archivo:
//
// 1. "Elabora el esqueleto de una clase MaxHeap que guarde pares (k-mer, conteo): los
//    atributos y las funciones heapifyUp, heapifyDown, construir, insertar, extraerMax y
//    topN, sin implementarlas."
//
// 2. "Revisa mi MaxHeap.h: verifica que heapifyDown compare bien con ambos hijos y que
//    topN no falle si n es mayor que la cantidad de k-mers. Senalame los errores."
#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include "TablaKmers.h"

class MaxHeap {
private:
    std::vector<KmerConteo> datos;

    void heapifyUp(int i) {
        while (i > 0) {
            int padre = (i - 1) / 2;
            if (datos[i].conteo > datos[padre].conteo) {
                KmerConteo tmp = datos[i];
                datos[i] = datos[padre];
                datos[padre] = tmp;
                i = padre;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int i) {
        int n = datos.size();
        while (true) {
            int izq = 2 * i + 1;
            int der = 2 * i + 2;
            int mayor = i;
            if (izq < n && datos[izq].conteo > datos[mayor].conteo) {
                mayor = izq;
            }
            if (der < n && datos[der].conteo > datos[mayor].conteo) {
                mayor = der;
            }
            if (mayor == i) break;
            KmerConteo tmp = datos[i];
            datos[i] = datos[mayor];
            datos[mayor] = tmp;
            i = mayor;
        }
    }

public:
    MaxHeap() {}

    void construir(const std::vector<KmerConteo>& conteos) {
        datos = conteos;
        int n = datos.size();
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    void insertar(const KmerConteo& kc) {
        datos.push_back(kc);
        heapifyUp(datos.size() - 1);
    }

    KmerConteo extraerMax() {
        KmerConteo maximo = datos[0];
        datos[0] = datos[datos.size() - 1];
        datos.pop_back();
        if (!datos.empty()) {
            heapifyDown(0);
        }
        return maximo;
    }

    void topN(const std::vector<KmerConteo>& conteos, int n) {
        construir(conteos);
        int total = datos.size();
        if (n > total) n = total;
        for (int i = 0; i < n; i++) {
            KmerConteo m = extraerMax();
            std::cout << m.kmer << "\t" << m.conteo << std::endl;
        }
    }
};

#endif // MAXHEAP_H_INCLUDED
