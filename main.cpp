#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Función para leer el contenido de un archivo y devolverlo como una cadena
string readFile(const string &path) {
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Failed to open " << path << endl;
        return "";
    }

    string line, content;
    while (getline(file, line)) {
        content += line + " ";
    }

    file.close();
    return content;
}

// Función para imprimir un vector
void printZValues(vector<int> &v){
    for(int i : v){
        cout << i << " ";
    }
    cout << endl;
}

// Función para encontrar coincidencias utilizando Z-function
vector<int> zNaive(string S){
    int n = S.length();
    vector<int> A(n,0);
    for(int i = 1; i<n; i++){
        for(int j = i; j<n;j++){
            if(S[j] == S[j-i]){
                A[i]++;
            }else
                break;
        }
    }
    return A;
}

// Parte 1
int analyzeTransmission(string tpath = "transmission1.txt", string mpath = "mcode1.txt"){
    // Procesamiento de los archivos
    ifstream transmissiontxt(tpath); 
    ifstream mcodetxt(mpath); 

    if(!transmissiontxt.is_open() || !mcodetxt.is_open()){
        cout << "Failed to open one of the files" << endl; 
    }

    string tline; 
    string transmission; 
    while(getline(transmissiontxt, tline)){
        transmission += tline + " ";
    }

    string mline; 
    string mcode; 
    while(getline(mcodetxt, mline)){
        mcode += mline + " ";
    }

    transmissiontxt.close(); 
    mcodetxt.close(); 
    // Procesamiento de los archivos

    // Análisis de los archivos
    string zString = mcode + "$" + transmission;
    vector<int> zValues = zNaive(zString);

    // Se busca una coincidencia, si existe se regresa la posición
    for(int i = 0; i < zValues.size(); i++){
        if(zValues[i] == mcode.length()){
            return i - mcode.length(); 
        }
    }

    return -1; 
}

// Parte 2: Buscar Palíndromos, saca la posición (iniciando en 1) en donde inicia y termina el código 
pair<int, string> longestPalindrome(const string &s) {
    int n = s.size();
    if (n == 0) return {0, ""}; // Si la cadena está vacía, retornar vacío

    int start = 0, maxLength = 1;

    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Todas las cadenas de un solo carácter son palíndromos
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // Verificar si hay palíndromos de longitud 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Verificar palíndromos de longitud mayor a 2
    for (int length = 3; length <= n; ++length) {
        for (int i = 0; i < n - length + 1; ++i) {
            int j = i + length - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLength = length;
            }
        }
    }

    return {start + 1, s.substr(start, maxLength)}; // Retorna posiciones 1-based y el palíndromo
}

void analyzePalindromes(const vector<string> &files) {
    for (const string &transmissionFile : files) {
        string transmission = readFile(transmissionFile);

        // Eliminamos espacios extra entre las líneas
        transmission.erase(remove(transmission.begin(), transmission.end(), ' '), transmission.end());

        if (!transmission.empty()) {
            pair<int, string> result = longestPalindrome(transmission);
            int startIdx = result.first;
            int endIdx = startIdx + result.second.size() - 1;

            // Imprimir las posiciones donde empieza y termina el palíndromo más largo
            
            cout << startIdx << " " << endIdx << " " << result.second << endl;
        } else {
            cout << "Error al leer el archivo " << transmissionFile << endl;
        }
    }
}

// Parte 3: Encontrar el substring común más largo entre dos cadenas
pair<int, int> longestCommonSubstring(const string &s1, const string &s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    int maxLength = 0;  // Longitud del substring común más largo
    int endIdx = 0;     // Índice donde termina el substring en s1

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIdx = i - 1;  // Guardar el índice final en s1
                }
            }
        }
    }

    return {endIdx - maxLength + 1, endIdx}; // Retorna las posiciones inicial y final del substring común en s1
}

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
    for (string transmissionFile : files) {
        for (string mcodeFile : mcodes) {
            int res = analyzeTransmission(transmissionFile, mcodeFile);
            if(res != -1){
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