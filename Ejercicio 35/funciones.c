#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Trabajo Pr�ctico 2/Trabajo-Practico-2-Memoria-din-mica/Ejercicio 35/main.c"

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
    printf("Tel�fono = ");
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
        printf("Tiene que ser mayor a 21 a�os\nNo se guardo el registro\n");
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