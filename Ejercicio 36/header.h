#ifndef MY_LIB
#define MY_LIB
#include <stdio.h>

typedef struct persona_pila{
        char nombre[30];
        char apellido[30];
        int edad;
        long telefono;
        char mail[100];
        struct persona_pila * lazo;
        }persona;

void leerArchivo(void);
void agregarRegistro(persona d);
void guardarLista(void);
void imprimirLista(void);

#endif