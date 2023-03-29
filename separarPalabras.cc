#include <iostream>
#include <fstream>
#include <list>
using namespace std;

string buscarPrefijo(string diccionario[12], string prefijo) {
    for (int i = 0; i < 12; i++) {
        if (diccionario[i] == prefijo) {
            cout << "Prefijo: " << prefijo << " -> existe en " << diccionario[i] << endl;
            return diccionario[i];
        }
    }
}

int main(int argc, char* argv[]) {
    string diccionario[12] = {"me", "gusta", "sol", "dar", "soldar", "dinámico", "hielo", "nata", "helado", "lado", "do", "la"};
    string entrada = "megustadolar";
    list<string> palabras;
    prueba(diccionario, entrada, 0, 0, palabras);
}
