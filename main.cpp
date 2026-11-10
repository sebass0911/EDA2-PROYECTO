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

int main() {
    TablaSecuencias tabla;
    bool cargado = false;
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n========== ANALISIS GENOMICO (HIV-2) ==========" << endl;
        cout << " 1. Cargar archivo FASTA (parte a + tabla 1)" << endl;
        cout << " 2. Buscar secuencia por ID (tabla 1)" << endl;
        cout << " 3. Contar k-mers de una secuencia (tabla 2)" << endl;
        cout << " 4. Top n k-mers mas frecuentes (max-heap)" << endl;
        cout << " 5. Matriz del grafo de 2-mers" << endl;
        cout << " 0. Salir" << endl;
        cout << "Opcion: ";
        if (!(cin >> opcion)) break;

        switch (opcion) {
            case 1: {
                cout << "[pendiente]" << endl;
                break;
            }
            case 2: {
                cout << "[pendiente]" << endl;
                break;
            }
            case 3: {
                cout << "[pendiente]" << endl;
                break;
            }
            case 4: {
                cout << "[pendiente]" << endl;
                break;
            }
            case 5: {
                cout << "[pendiente]" << endl;
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
