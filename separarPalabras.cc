/*
* AUTORES:     Diego Domingo Ralla (818637)
*              Simón Alonso Gutiérrez (821038)
* ASIGNATURA:  Algoritmia Básica
* FECHA:       21 abril 2023
* FICHERO:     separarPalabras.cc
* DESCRIPCIÓN: Programa que dada una cadena de entrada y un dict de
*              palabras, encuentra si la cadena se puede subdividir en una
*              secuencia de palabras del dict separada por espacios en
*              blanco
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <chrono>
#include <random>
using namespace std;
using namespace chrono;

// Busca si un prefijo se encuentra entre las palabras de un diccionario
// Pre:
// Post: true <-> ∃i ∈ dict t.q dict[i] = prefijo
bool buscarPrefijo(unordered_set<string>& dict, string prefijo) {
    return dict.count(prefijo);
}

// Busca, si las hay, todas las secuencias de palabras de dict en que se puede
// dividir la cadena entrada
// Pre:  i <= |entrada|
// Post: devuelve en particion los prefijos de entrada que se encuentran en 
//       dict, y en resultado cada una de las combinaciones de prefijos
//       encontrados, separados por espacios en blanco
void descubrirSecuencia(unordered_set<string>& dict, string entrada, int i, 
                         vector<string>& particion, vector<string>& resultado) {
    // Si es el final de la secuencia, se guarda en resultado
    if (i == entrada.length()) {
        string res = "";
        for (int i = 0; i < particion.size(); i++) {
            if (i == particion.size() - 1) {
                res += particion[i];
            }
            else {
              res += particion[i] + " ";
            }
        }
        resultado.push_back(res);
    }
    // Recorrer todas las subcadenas desde el indice actual
    for (int j = i + 1; j <= entrada.length(); j++) {
        string prefijo = entrada.substr(i, j - i);
        // Si se encuentra prefijo, se añade el prefijo a la particiones
        if (buscarPrefijo(dict, prefijo)) {
            particion.push_back(prefijo);
            descubrirSecuencia(dict, entrada, j, particion, resultado);
            particion.pop_back();
        }
    }
}

// Genera una entrada formada por palabras aleatorias de un diccionario
// Pre:
// Post: devuelve en entrada la concatenación de |dict| / 10 palabras de dict
string generarEntrada(unordered_set<string> dict) {
    string entrada = "";
    int palabras = dict.size() / 10;
    srand(time(0));
    auto it = dict.begin(); // Iterador para recorrer dict
    advance(it, rand() % dict.size()); // Avanzar el iterador aleatoriamente
    for (int i = 0; i < palabras; i++) {
        entrada += *it; // Se concatena en entrada la palabra apuntada por el iterador
        // Reinicio del iterador y cálculo de la siguiente palabra
        it = dict.begin();
        advance(it, rand() % dict.size()); 
    }
    return entrada;
}

// Modifica de forma aleatoria la cadena entrada
// Pre:
// Post: devuelve en entrada la cadena original modificada de forma aleatoria,
//       de manera que cada letra tiene una probabilidad de ser cambiada por
//       otra cualquiera de 1 / (|entrada| * 10)
string modificarEntrada(string entrada) {
    int lf = entrada.length();
    srand(time(0));
    for (int i = 0; i < lf; i++) {
        double numero = double(rand()) / RAND_MAX;
        // Si el número generado es menor o igual que 1 / (lf * 10) y la letra
        // es un caracter ASCII (no es tilde) se cambia por otra letra aleatoria
        if (numero <= 1.0 / (lf * 10) && isascii(entrada[i])) {
            entrada[i] = char(rand() % 26 + 'a');
        }
    }
    return entrada;
}

int main(int argc, char* argv[]) {
    unordered_set<string> dict;

    if (argc != 4) {
        cerr << "Uso: separarPalabras <dict.txt> <salida.txt> <modificar entrada (0 o 1)>" << endl;
        return -1;
    }

    ifstream f;
    f.open(argv[1]);
    if (f.is_open()) {
        string linea;
        while (!f.eof()) {
            getline(f, linea);
            dict.insert(linea);
        }
        f.close();
    }
    
    // Se genera automáticamente una entrada con las palabras del diccionario
    string entrada = generarEntrada(dict);
    // Si se quiere, se modifica la entrada generada de manera aleatoria
    if (atoi(argv[3]) == 1) {
        entrada = modificarEntrada(entrada);
    }
    cout << "La entrada es: \"" + entrada + "\"" << endl;

    auto start = high_resolution_clock::now(); 

    // Se buscan las secuencias de palabras para entrada
    vector<string> particion;
    vector<string> resultado;
    descubrirSecuencia(dict, entrada, 0, particion, resultado);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start); 
    cout << "Tiempo de ejecución: " << duration.count()/1E6 << " milisegundos" << endl;

    ofstream g;
    g.open(argv[2], ios::trunc);
    if (g.is_open()) {
        if (resultado.empty()) {
            g << "No se ha encontrado partición" << endl;
        }
        else {
            for (int i = 0; i < resultado.size(); i++) {
                g << resultado[i] << endl;
            }
        }
        g.close();
    }
    
    return 0;
}