#include <iostream>
#include <vector>
#include <string>
#include "transmission.h"

using namespace std;

int main() {
    vector<string> files;
    vector<string> mcodes;
    files.push_back("transmission1.txt");
    files.push_back("transmission2.txt");
    mcodes.push_back("mcode1.txt");
    mcodes.push_back("mcode2.txt");
    mcodes.push_back("mcode3.txt");

    // Parte 1: Verificar si los archivos de transmisión contienen los mcodes
    cout << "Parte 1: " << endl;
    for (const string &transmissionFile : files) {
        for (const string &mcodeFile : mcodes) {
            int res = analyzeTransmission(transmissionFile, mcodeFile);
            if (res != -1) {
                cout << "true " << res << endl;
            } else {
                cout << "false " << endl; 
            }
        }
    }

    // Parte 2: Encontrar el palíndromo más largo
    cout << "Parte 2: " << endl;
    analyzePalindromes(files);

    // Parte 3: Encontrar el substring común más largo entre transmission1.txt y transmission2.txt
    cout << "Parte 3:" << endl;
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");

    if (!transmission1.empty() && !transmission2.empty()) {
        pair<int, int> result = longestCommonSubstring(transmission1, transmission2);
        int startIdx = result.first;
        int endIdx = result.second;

        // Obtener el substring común
        string commonSubstring = transmission1.substr(startIdx, endIdx - startIdx + 1);

        // Imprimir las posiciones y el substring común
        cout << startIdx + 1 << " " << endIdx + 1 << " " << commonSubstring << endl;
    } else {
        cout << "Error al leer los archivos de transmisión." << endl;
    }

    return 0;
}
