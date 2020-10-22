# Ejercicio 35

Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.

# Archivo main

```c
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
```
# Archivo header
```h
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
```
# Archivo funciones
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

str_aux apilar(persona p_pila, str_aux ap)
{
    //Reservo el espacio de memoria
    ap.aux = (struct persona_pila *) malloc(sizeof(struct persona_pila));
    if(ap.aux)
    {
        //Cargo los datos
        printf("%s\n",ap.aux->nombre);
        strcpy(ap.aux->nombre,p_pila.nombre);
        strcpy(ap.aux->apellido,p_pila.apellido);
        ap.aux->edad = p_pila.edad;
        ap.aux->telefono = p_pila.telefono;
        strcpy(ap.aux->mail,p_pila.mail);
        //Hago que el lazo apunte al primero
        ap.aux->lazo = ap.p;
        //El primero apunta al creado
        ap.p = ap.aux;
    } else {
        printf("Memoria insuficiente\n");
    }
    return ap;
}

str_aux escribir(str_aux ap)
{
    persona d;
    fflush(stdin);
    printf("Nombre = ");
    scanf("%s",d.nombre);
    fflush(stdin);
    printf("Apellido = ");
    scanf("%s",d.apellido);
    fflush(stdin);
    printf("Edad = ");
    scanf("%d",&d.edad);
    fflush(stdin);
    printf("Teléfono = ");
    scanf("%ld",&d.telefono);
    fflush(stdin);
    printf("Mail = ");
    scanf("%s",d.mail);
    fflush(stdin);
    if(d.edad > 21)
    {
        ap = apilar(d,ap);
        FILE *p;
        p = fopen("contactos.dat","ab");
        fwrite(&d,sizeof(d),1,p);
        fclose(p);
        system("cls");
        printf("Registro guardado\n");
        system("pause");
    } else {
        system("cls");
        printf("Tiene que ser mayor a 21 años\nNo se guardo el registro\n");
        system("pause");
    }
    return ap;
}

void mostrar()
{
    persona d;
    FILE *p;
    p = fopen("contactos.dat","rb");
    if(p != NULL)
    {
        printf("  Nombre  Apellido  Edad  Telefono   Mail\n\n");
        fread(&d,sizeof(d),1,p);
        while(!feof(p))
        {
            fprintf(stdout,"  %s  %-8s   %-2d  %-10ld  %s\n",d.nombre,d.apellido,d.edad,d.telefono,d.mail);
            fread(&d,sizeof(d),1,p);
        }
    } else {
        printf("No hay archivos guardados.\n");
    }
    printf("\n");
    system("pause");
    fclose(p);
}
```
