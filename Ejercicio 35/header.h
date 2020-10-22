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
        struct persona_pila *p, *aux;
        } str_aux;

str_aux escribir(str_aux ap);
void mostrar(void);

#endif
