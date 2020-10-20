#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Trabajo Práctico 2/Trabajo-Practico-2-Memoria-din-mica/Ejercicio 35/header.h"
#include "../Trabajo Práctico 2/Trabajo-Practico-2-Memoria-din-mica/Ejercicio 35/funciones.c"

struct persona_pila *p = NULL, *aux;

int main()
{
    int op;
    do
    {
        printf("******Menu*******\n");
        printf("1.Escribir un registro\n");
        printf("2.Mostrar lista\n");
        printf("3.Salir\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                system("cls");
                escribir();
                break;
            case 2:
                system("cls");
                mostrar();
                break;
        }
        system("cls");
    }while(op != 3);
    return 0;
}


