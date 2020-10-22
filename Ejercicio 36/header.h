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

typedef struct{
        struct persona_pila *p, *u, *aux, *r;
        } str_aux;

void leerArchivo(str_aux ap);
str_aux agregarRegistro(persona d, str_aux ap);
void guardarLista(str_aux ap);
void imprimirLista(void);

#endif