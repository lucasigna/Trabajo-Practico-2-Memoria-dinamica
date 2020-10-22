# Ejercicio 37
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:
```c
struct d {                                                                                            
long clave; //Clave o Id del registro

char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
```
Se Pide: Realizar una función que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.

# Archivo main

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long clave; //Clave o Id del registro

    char d[30]; // Descripcion
    unsigned char tipo; //Tipo de datos como entero sin signo
    char b; //'A':Alta 'B':Baja
    } registro;

struct d {
    int id;
    long clave;
    struct d * lazo;
    };

typedef struct{
    int i;
    struct d *p, *aux;
    } str_aux;

str_aux buscar(long clave, str_aux ap);

int main()
{
    str_aux ap;
    ap.p = NULL;
    ap.i = 1;
    long clave;
    int op;
    do
    {
        printf("******Menu*******\n");
        printf("1.Buscar un registro\n");
        printf("2.Salir\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                system("cls");
                printf("Clave a buscar: ");
                scanf("%ld",&clave);
                fflush(stdin);
                ap = buscar(clave,ap);
                break;
        }
        system("cls");
    }while(op != 2);
    return 0;
}

str_aux buscar(long clave, str_aux ap)
{
    registro data;
    int encontro = 0;
    FILE *p;
    p = fopen("datos.dat","rb");
    if(p != NULL)
    {
        fread(&data,sizeof(data),1,p);
        while(!feof(p))
        {
            if(data.clave == clave && data.b == 'A')
            {
                //Encontró
                encontro = 1;
                break;
            }
            fread(&data,sizeof(data),1,p);
        }
    }
    if(encontro)
    {
        printf("Clave: %ld\nDescripcion: %s",data.clave,data.d);
        //Me fijo el tipo
        if(data.tipo&(0b00010000))
        {
            //Tengo que apilarlo
            ap.aux = (struct d *) malloc(sizeof(struct d));
            if(ap.aux)
            {
                ap.aux->clave = data.clave;
                ap.aux->id = ap.i;
                ap.aux->lazo = ap.p;
                ap.p = ap.aux;
                ap.i++;
            } else {
                printf("Memoria insuficiente\n");
            }
        }
    } else {
        printf("Registro no encontrado");
    }
    printf("\n");
    system("pause");
    fclose(p);
    return ap;
}
```