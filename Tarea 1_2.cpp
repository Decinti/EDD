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

int* comprarTarjeta(string nombre, int dia, int &m) {
    m = nombre.size();
    int* tarjeta = new int[m];
    for (int i = 0; i < m; ++i) {
        tarjeta[i] = nombre[i] % dia;
    }
    return tarjeta;
}

void intercambiarTarjeta(Persona* p1, Persona* p2) {
    int *temp = p1->tarjeta;
    p1->tarjeta = p2->tarjeta;
    p2->tarjeta = temp;

    int temp_tamanio = p1->tamanio_tarjeta;
    p1->tamanio_tarjeta = p2->tamanio_tarjeta;
    p2->tamanio_tarjeta = temp_tamanio;
}

bool tieneNumeroEnComun(Persona *p1, Persona *p2) {
    for (int i = 0; i < p1->tamanio_tarjeta; ++i) {
        for (int j = 0; j < p2->tamanio_tarjeta; ++j) {
            if (p1->tarjeta[i] == p2->tarjeta[j]) {
                return true;
            }
        }
    }
    return false;
}

int puntaje(Persona* p1) {
    int suma = 0;
    for (int i = 0; i < p1->tamanio_tarjeta; ++i) {
        suma += p1->tarjeta[i] * (p1->fecha[i % 10] - '0');
    }
    return suma;
}

Persona* unDia(Persona* personas, int n, int dia) {
    for (int i = 0; i < n; ++i) {
        int m;
        personas[i].tarjeta = comprarTarjeta(personas[i].nombre, dia, m);
        personas[i].tamanio_tarjeta = m;
    }
    
    for (int i = 0; i < n; ++i) {
        if (personas[i].quiere_intercambiar) {
            for (int j = 0; j < n; ++j) {
                if (i != j && personas[j].quiere_intercambiar && tieneNumeroEnComun(&personas[i], &personas[j])) {
                    intercambiarTarjeta(&personas[i], &personas[j]);
                    personas[i].quiere_intercambiar = false;
                    break;
                }
            }
        }
    }

    int max_puntaje = puntaje(&personas[0]);
    int max_indice = 0;
    for (int i = 1; i < n; ++i) {
        int p = puntaje(&personas[i]);
        if (p > max_puntaje) {
            max_puntaje = p;
            max_indice = i;
        }
    }

    return &personas[max_indice];
}

void variosDias(Persona* personas, int n, int cant_dias) {
    for (int i = 1; i <= cant_dias; ++i) {
        Persona *ganador = unDia(personas, n, i);
       
