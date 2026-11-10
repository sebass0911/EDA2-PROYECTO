//responsable: Sebastian
//  Prompts de IA usados en este archivo;

#include <iostream>
#include <string>
#include <vector>
#include "DNASequence.h"
#include "Parser.h"
#include "TablaSecuencias.h"
#include "TablaKmers.h"
#include "MaxHeap.h"
#include "Grafo.h"
using namespace std;

const string ARCHIVO = "HIV2_ALL_2021_env_DNA.2000.fasta";

int pedirEntero(const string& mensaje, int minimo, int maximo) {
    int valor;
    while (true) {
        cout << mensaje << " (" << minimo << "-" << maximo << "): ";
        if (cin >> valor && valor >= minimo && valor <= maximo) return valor;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Valor no valido." << endl;
    }
}

DNASequence* pedirSecuencia(TablaSecuencias& tabla, bool cargado) {
    if (!cargado) {
        cout << "Primero carga el archivo (opcion 1)." << endl;
        return nullptr;
    }
    string id;
    cout << "ID de la secuencia: ";
    cin >> id;
    DNASequence* s = tabla.buscar(id);
    if (s == nullptr) cout << "No existe una secuencia con ID " << id << endl;
    return s;
}

int main() {
    TablaSecuencias tabla;
    vector<DNASequence> secuencias;
    bool cargado = false;
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n========== ANALISIS GENOMICO (HIV-2) ==========" << endl;
        cout << " 1. Cargar archivo FASTA (parte a + tabla 1)" << endl;
        cout << " 2. Buscar secuencia por ID (tabla 1)" << endl;
        cout << " 3. Contar k-mers de una secuencia (tabla 2)" << endl;
        cout << " 4. Top n k-mers mas frecuentes (max-heap)" << endl;
        cout << " 5. Matriz del grafo de 2-mers" << endl;
        cout << " 6. Comparar double hashing vs linear probing" << endl;
        cout << " 0. Salir" << endl;
        cout << "Opcion: ";
        if (!(cin >> opcion)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1: {
                if (cargado) {
                    cout << "El archivo ya esta cargado." << endl;
                    tabla.mostrarEstado();
                    break;
                }
                secuencias = leerFasta(ARCHIVO);
                tabla.verbose = true;
                int repetidas = 0;
                for (size_t i = 0; i < secuencias.size(); i++) {
                    if (!tabla.insertar(secuencias[i])) repetidas++;
                }
                cargado = true;
                cout << "Secuencias leidas: " << secuencias.size()
                     << " | repetidas: " << repetidas << endl;
                tabla.mostrarEstado();
                break;
            }
            case 2: {
                DNASequence* s = pedirSecuencia(tabla, cargado);
                if (s == nullptr) break;
                cout << "ID: " << s->id << endl;
                cout << "Largo: " << s->sequence.length() << " nucleotidos" << endl;
                cout << "Inicio: " << s->sequence.substr(0, 60) << "..." << endl;
                break;
            }
            case 3: {
                DNASequence* s = pedirSecuencia(tabla, cargado);
                if (s == nullptr) break;
                int k = pedirEntero("Tamano k", 1, 10);
                TablaKmers tk(k);
                tk.contar(s->sequence);
                tk.mostrar();
                tk.mostrarEstado();
                string kmer;
                cout << "k-mer a buscar (o - para omitir): ";
                cin >> kmer;
                if (kmer != "-") {
                    cout << kmer << " aparece " << tk.buscar(kmer) << " veces" << endl;
                }
                break;
            }
            case 4: {
                DNASequence* s = pedirSecuencia(tabla, cargado);
                if (s == nullptr) break;
                int k = pedirEntero("Tamano k", 1, 10);
                int n = pedirEntero("Cuantos k-mers mostrar", 1, 1000);
                TablaKmers tk(k);
                tk.contar(s->sequence);
                topN(tk.obtenerTodos(), n);
                break;
            }
            case 5: {
                DNASequence* s = pedirSecuencia(tabla, cargado);
                if (s == nullptr) break;
                double beta;
                cout << "Valor de beta: ";
                while (!(cin >> beta) || beta <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor no valido. Valor de beta: ";
                }
                grafoKmers(s->sequence, beta);
                break;
            }
            case 6: {
                if (!cargado) {
                    cout << "Primero carga el archivo (opcion 1)." << endl;
                    break;
                }
                int k = pedirEntero("Tamano k", 1, 10);
                double dhIns = 0, dhBus = 0, lpIns = 0, lpBus = 0, alfa = 0;
                for (size_t i = 0; i < secuencias.size(); i++) {
                    TablaKmers dh(k, true);
                    TablaKmers lp(k, false);
                    dh.contar(secuencias[i].sequence);
                    lp.contar(secuencias[i].sequence);
                    dhIns += dh.promedioSondeosInsercion();
                    dhBus += dh.promedioSondeosBusqueda();
                    lpIns += lp.promedioSondeosInsercion();
                    lpBus += lp.promedioSondeosBusqueda();
                    alfa += dh.factorCarga();
                }
                int total = secuencias.size();
                cout << "Promedio sobre " << total << " secuencias, k = " << k
                     << " (" << (int)pow(4, k) << " bins, factor de carga " << alfa / total << ")" << endl;
                cout << "                   Insertar   Buscar" << endl;
                cout << "Double hashing:    " << dhIns / total << "    " << dhBus / total << endl;
                cout << "Linear probing:    " << lpIns / total << "    " << lpBus / total << endl;
                cout << endl;
                tabla.mostrarEstado();
                break;
            }
            case 0:
                cout << "Adios." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    }
    return 0;
}
