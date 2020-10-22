#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "funciones.c"

int main()
{
    str_aux ap;
    ap.p = NULL;

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
                ap = escribir(ap);
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


