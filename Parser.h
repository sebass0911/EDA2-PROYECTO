#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct DNASequence {
    std::string id;
    std::string sequence;
};

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
