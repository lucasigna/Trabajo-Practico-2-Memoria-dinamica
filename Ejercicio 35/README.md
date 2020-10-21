# Ejercicio 35

Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.

# Archivo main

```c
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

void escribir(void);
void mostrar(void);

#endif
```
# Archivo funciones
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Trabajo Práctico 2/Trabajo-Practico-2-Memoria-din-mica/Ejercicio 35/main.c"

void apilar(persona p_pila)
{
    //Reservo el espacio de memoria
    aux = (struct persona_pila *) malloc(sizeof(struct persona_pila));
    if(aux)
    {
        //Cargo los datos
        strcpy(aux->nombre,p_pila.nombre);
        strcpy(aux->apellido,p_pila.apellido);
        aux->edad = p_pila.edad;
        aux->telefono = p_pila.telefono;
        strcpy(aux->mail,p_pila.mail);
        //Hago que el lazo apunte al primero
        aux->lazo = p;
        //El primero apunta al creado
        p = aux;
    } else {
        printf("Memoria insuficiente\n");
    }
}

void escribir()
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
        apilar(d);
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
