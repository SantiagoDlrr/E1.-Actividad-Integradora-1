#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

// Funcion para imprimir un vector, en este caso el vector que contiene las coincidencias
void printZValues(vector<int> &v){
    for(int i : v){
        cout << i << " ";
    }
    cout << endl;
}

// Funcion para encontrar coincidencias utilizando Z-function
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
    

    // Funcion para ver el vector que contiene donde se encontro el patrón
    //printZValues(zValues);

    // Se busca una coincidencia, si existe se regresa la posición
    for(int i = 0; i < zValues.size(); i++){
        if(zValues[i] == mcode.length()){
            return i - mcode.length(); 
        }
    }

    return -1; 
}

int main() {
    vector<string> files;
    vector<string> mcodes;
    files.push_back("transmission1.txt");
    files.push_back("transmission2.txt");
    mcodes.push_back("mcode1.txt");
    mcodes.push_back("mcode2.txt");
    mcodes.push_back("mcode3.txt");

    cout << "Parte 1: " << endl;
    for (string transmissionFile : files) {
        for (string mcodeFile : mcodes) {
            int res = analyzeTransmission(transmissionFile, mcodeFile);
            if(res != -1){
                cout << "true " << res << endl; ;
            }else{
                cout << "false " << endl; 
            }
        }
    }
    return 0;
}
