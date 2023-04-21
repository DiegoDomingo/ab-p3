#
# AUTORES:     Diego Domingo Ralla (818637)
#              Simón Alonso Gutiérrez (821038)
# ASIGNATURA:  Algoritmia Básica
# FECHA:       21 abril 2023
# FICHERO:     ejecutar.sh
# DESCRIPCIÓN: Script de ejecución que automatiza la compilación y ejecución del
#              programa con varios casos de prueba
#

#!/bin/bash

# Compilación de los fuentes
g++ -std=c++11 separarPalabras.cc -o separarPalabras

rm descifrado.txt 2>/dev/null

echo "*********"
echo "Prueba $i"
echo "*********"

# Ejecución de los programas
./separarPalabras dict100.txt salida100-1.txt 0
./separarPalabras dict100.txt salida100-2.txt 1
./separarPalabras dict1000.txt salida1000-1.txt 0
./separarPalabras dict1000.txt salida1000-2.txt 1

# Limpieza de ejecutables y ficheros generados
rm separarPalabras 2>/dev/null
