#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool buscarPrefijo(vector<string> diccionario, string prefijo) {
    int n = diccionario.size();
    for (int i = 0; i < n; i++) {
        if (diccionario.at(i) == prefijo) {
            return true;
        }
    }
    return false;
}

void descubrir_secuencia(vector<string> dict, string entrada, int i,vector<string> particion) {
    //Si es el final de la cadena, imprimimos las particiones encontradas hasta ahora
    if (i >= entrada.length()) { 
        for (auto v : particion){
            cout << v << " ,";
        }
        cout << endl;
    }

    //Recorrer todas las subcadenas desde el indice actual
    for (int j = i+1; j <= entrada.length(); j++) { 
        string prefijo = entrada.substr(i, j-i);
        //Si encontramos prefijo, añadimo el prefijo a la particion
        if (buscarPrefijo(dict,prefijo)) { 
            particion.push_back(prefijo);
            descubrir_secuencia(dict,entrada,j,particion);
            //Si no se hace pop_back() se acumula el ultimo prefijo.
            //Entonces en lugar de hacerlo bien hace: sol, soldar
            particion.pop_back(); 
        }
    }
}

int main() {
    vector<string> diccionario= {"me", "gusta", "sol", "dar","d", "ar", "soldar", "soldar", "dinámico", "hielo", "nata", "helado", "lado", "do", "la"};
    string entrada = "megustasoldar";
    vector<string> particion;
    descubrir_secuencia(diccionario, entrada, 0, particion);
}