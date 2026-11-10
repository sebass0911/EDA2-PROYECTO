//Responsable: Alessandro
//  Prompts de IA usados en este archivo
//
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DNASequence.h"
using namespace std;

vector<DNASequence> leerFasta(const string& ruta) {
    vector<DNASequence> secuencias;

    // TODO (Alessandro):
    //  1. Abrir el archivo con ifstream
    //  2. Leer linea por linea con getline
    //  3. Si la linea empieza con '>': empieza una secuencia nueva (id = linea sin el '>').
    //  4. Si no: agregar la linea al 'sequence' de la secuencia actual.

    return secuencias;
}
