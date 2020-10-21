#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.c"

void leerArchivo()
{
    persona d;
    FILE *f;
    f = fopen("contactos.dat","rb");
    if(f != NULL)
    {
        fread(&d,sizeof(d),1,f);
        while(!feof(f))
        {
            agregarRegistro(d);
            fread(&d,sizeof(d),1,f);
        }
    } else {
        printf("No hay archivos guardados.\n");
    }
    printf("\n");
    guardarLista();
    fclose(f);
}
void agregarRegistro(persona d)
{
    aux = (struct persona_pila *) malloc(sizeof(struct persona_pila));
    if(aux)
    {
        strcpy(aux->nombre,d.nombre);
        strcpy(aux->apellido,d.apellido);
        aux->edad = d.edad;
        aux->telefono = d.telefono;
        strcpy(aux->mail,d.mail);
        if(p == NULL)
        {
            p=u=aux;
            u->lazo = NULL;
        } else {
            r = p;
            while(1)
            {
                if(strcmp(r->apellido,aux->apellido) > 0)
                {
                    aux->lazo = p;
                    p = aux;
                    break;
                }
                while(r->lazo)
                {
                    if(strcmp(r->lazo->apellido,aux->apellido) < 0 )
                    {
                        r = r->lazo;
                    } else {
                        break;
                    }
                }
                if(r == u)
                {
                    u->lazo = aux;
                    u = aux;
                    u->lazo = NULL;
                    break;
                }
                aux->lazo = r->lazo;
                r->lazo = aux;
                break;
            }
        }
    }
}
void guardarLista()
{
    FILE *f;
    f = fopen("contactos_ordenados.dat","ab");
    aux = p;
    while(aux)
    {
        ///Guardar registro
        persona d;
        strcpy(d.nombre,aux->nombre);
        strcpy(d.apellido,aux->apellido);
        d.edad = aux->edad;
        d.telefono = aux->telefono;
        strcpy(d.mail,aux->mail);
        fwrite(&d,sizeof(d),1,f);
        aux = aux->lazo;
    }
    fclose(f);
    imprimirLista();
}
void imprimirLista()
{
    persona d;
    FILE *f;
    f = fopen("contactos_ordenados.dat","rb");
    if(f != NULL)
    {
        printf("  Apellido  Nombre    Edad  Telefono   Mail\n\n");
        fread(&d,sizeof(d),1,f);
        while(!feof(f))
        {
            fprintf(stdout,"  %-8s  %-8s   %-2d  %-10ld  %s\n",d.apellido,d.nombre,d.edad,d.telefono,d.mail);
            fread(&d,sizeof(d),1,f);
        }
    }
    printf("\n");
    system("pause");
    fclose(f);
}