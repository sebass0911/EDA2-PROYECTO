// Responsable: Alessandro
// Prompts de IA usados en este archivo:
//
// 1. "Explicame como esta organizado un archivo FASTA y que pasos deberia seguir para
//    leerlo linea por linea y separar el identificador de la secuencia."
//
// 2. "Revisa mi funcion leerFasta: el programa no encuentra las secuencias por su ID.
//    Indicame donde esta el error y por que ocurre."
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "DNASequence.h"


std::vector<DNASequence> leerFasta(const std::string& ruta) {
    std::vector<DNASequence> secuencias;
    std::ifstream archivo(ruta);
    if(!archivo.is_open()) {
        return secuencias;
    }

    std::string linea;
    DNASequence actual;
    bool tieneActual = false;

    while (std::getline(archivo, linea)) {
        if (!linea.empty() && linea[linea.size() - 1] == '\r') {
            linea = linea.substr(0, linea.size() - 1);
        }
        if (linea.empty()) continue;

        if (linea[0] == '>') {
            if (tieneActual) {
                secuencias.push_back(actual);
            }
            actual.id = linea.substr(1);
            actual.sequence = "";
            tieneActual = true;
        } else {
            actual.sequence = actual.sequence + linea;
        }
    }

    if (tieneActual) {
        secuencias.push_back(actual);
    }
    archivo.close();
    return secuencias;


}


#endif // PARSER_H_INCLUDED
