# Ejercicio 38
Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal, en 8 bits, para luego recorrerla y recomponer la señal completa. Las muetras deberán ir de 127 a -127 utilizando el bit más significativo en 1 para los valores negativos y en 0 para los valores positivos. Imprimir en pantalla los valores.

# Archivo main

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

struct valor{
        char dato;
        struct valor *lazo;
        };

typedef struct{
        struct valor *p, *u, *aux;
        } str_aux;

str_aux cargarDatos(str_aux ap);
void recorrer_y_mostrar(str_aux ap);

int main()
{
    str_aux ap;
    ap.p = NULL;
    ap.u = NULL;
    ap = cargarDatos(ap);
    recorrer_y_mostrar(ap);
    return 0;
}


str_aux cargarDatos(str_aux ap)
{
    int i;
    for(i = 1; i<=9 ; i++)
    {
        ap.aux = (struct valor*) malloc(sizeof(struct valor));
        if(ap.aux)
        {
            ap.aux->dato = sin((i*10*PI)/180)*127;
            if(ap.p == NULL)
            {
                ap.p = ap.aux;
                ap.u = ap.aux;
            } else {
                ap.u->lazo = ap.aux;
                ap.u = ap.aux;
            }
            ap.u->lazo = NULL;
        }
    }
    return ap;
}

void recorrer_y_mostrar(str_aux ap)
{
    int i = 0,j,k,m;
    char top;
    ap.aux = ap.p;
    while(ap.aux)
    {
        i = i+10;
        printf("  %-6d %d Grados\n",ap.aux->dato,i);
        if(i == 90)
        {
            top = ap.aux->dato;

        }
        ap.aux = ap.aux->lazo;
    }
    for(j = 8 ; j>=0 ; j--)
    {
        i = i+10;
        int nuevo = sin((j*10*PI)/180)*top;
        printf("  %-6d %d Grados\n",nuevo,i);
    }
    for(k = 1 ; k<=9 ; k++)
    {
        i = i+10;
        int nuevo = sin((k*10*PI)/180)*top;
        printf("  %-6d %d Grados\n",-nuevo,i);
    }
    for(m = 8 ; m>=0 ; m--)
    {
        i = i+10;
        int nuevo = sin((m*10*PI)/180)*top;
        printf("  %-6d %d Grados\n",-nuevo,i);
    }
}
```
