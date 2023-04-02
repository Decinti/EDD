#include <iostream>
#include <string>
using namespace std;

struct Persona {
    string nombre;
    char fecha[11];
    int tamanio_tarjeta;
    int *tarjeta;
    bool quiere_intercambiar;
};

// Función para comprar una tarjeta de la suerte
int* comprarTarjeta(string nombre, int dia, int &m) {
    m = nombre.size(); // El tamaño de la tarjeta es igual al tamaño del nombre
    int* tarjeta = new int[m]; // Crear un arreglo dinámico para la tarjeta

    // Llenar la tarjeta con los valores calculados
    for (int i = 0; i < m; ++i) {
        tarjeta[i] = nombre[i] % dia;
    }

    return tarjeta; // Devolver la tarjeta generada
}

// Función para intercambiar tarjetas entre dos personas
void intercambiarTarjeta(Persona* p1, Persona* p2) {
    // Intercambiar punteros a las tarjetas
    int *temp = p1->tarjeta;
    p1->tarjeta = p2->tarjeta;
    p2->tarjeta = temp;

    // Intercambiar tamaños de las tarjetas
    int temp_tamanio = p1->tamanio_tarjeta;
    p1->tamanio_tarjeta = p2->tamanio_tarjeta;
    p2->tamanio_tarjeta = temp_tamanio;
}

// Función para verificar si dos personas tienen algún número en común en sus tarjetas
bool tieneNumeroEnComun(Persona *p1, Persona *p2) {
    for (int i = 0; i < p1->tamanio_tarjeta; ++i) {
        for (int j = 0; j < p2->tamanio_tarjeta; ++j) {
            if (p1->tarjeta[i] == p2->tarjeta[j]) {
                return true; // Encontró un número en común
            }
        }
    }
    return false; // No hay números en común
}

// Función para calcular el puntaje de una persona
int puntaje(Persona* p1) {
    int suma = 0;
    for (int i = 0; i < p1->tamanio_tarjeta; ++i) {
        suma += p1->tarjeta[i] * (p1->fecha[i % 10] - '0');
    }
    return suma; // Devolver el puntaje calculado
}

// Función que simula un día en Cplusplusiano
Persona* unDia(Persona* personas, int n, int dia) {
    // Comprar tarjetas para todas las personas
    for (int i = 0; i < n; ++i) {
        int m;
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre, dia, m);
        personas[i].tamanio_tarjeta = m;
    }

    // Intentar intercambiar tarjetas entre las personas que quieren hacerlo
    for (int i = 0; i < n; ++i) {
        if (personas[i].quiere_intercambiar) {
            for (int j = 0; j < n; ++j) {
                if (i != j && personas[j].quiere_intercambiar && tieneNumeroEnComun(&personas[i], &personas[j])) {
                    intercambiarTarjeta(&personas[i], &personas[j]);
                }
            }
        }
    }