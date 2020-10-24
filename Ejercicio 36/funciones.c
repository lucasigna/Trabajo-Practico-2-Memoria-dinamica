#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.c"

void leerArchivo(str_aux ap)
{
    persona d;
    FILE *f;
    f = fopen("contactos.dat","rb");
    if(f != NULL)
    {
        fread(&d,sizeof(d),1,f);
        while(!feof(f))
        {
            ap = agregarRegistro(d,ap);
            fread(&d,sizeof(d),1,f);
        }
    } else {
        printf("No hay archivos guardados.\n");
    }
    printf("\n");
    guardarLista(ap);
    fclose(f);
}
str_aux agregarRegistro(persona d, str_aux ap)
{
    ap.aux = (struct persona_pila *) malloc(sizeof(struct persona_pila));
    if(ap.aux)
    {
        strcpy(ap.aux->nombre,d.nombre);
        strcpy(ap.aux->apellido,d.apellido);
        ap.aux->edad = d.edad;
        ap.aux->telefono = d.telefono;
        strcpy(ap.aux->mail,d.mail);
        if(ap.p == NULL)
        {
            ap.p=ap.u=ap.aux;
            ap.u->lazo = NULL;
        } else {
            ap.r = ap.p;
            if(strcmp(ap.r->apellido,ap.aux->apellido) > 0)
            {
                ap.aux->lazo = ap.p;
                ap.p = ap.aux;
            } else {
                while(ap.r->lazo)
                {
                    if(strcmp(ap.r->lazo->apellido,ap.aux->apellido) < 0 )
                    {
                        ap.r = ap.r->lazo;
                    }
                }
                if(ap.r == ap.u)
                {
                    ap.u->lazo = ap.aux;
                    ap.u = ap.aux;
                    ap.u->lazo = NULL;
                } else {
                    ap.aux->lazo = ap.r->lazo;
                    ap.r->lazo = ap.aux;
                }
            }
        }
    }
    return ap;
}
void guardarLista(str_aux ap)
{
    FILE *f;
    f = fopen("contactos_ordenados.dat","ab");
    ap.aux = ap.p;
    while(ap.aux)
    {
        ///Guardar registro
        persona d;
        strcpy(d.nombre,ap.aux->nombre);
        strcpy(d.apellido,ap.aux->apellido);
        d.edad = ap.aux->edad;
        d.telefono = ap.aux->telefono;
        strcpy(d.mail,ap.aux->mail);
        fwrite(&d,sizeof(d),1,f);
        ap.aux = ap.aux->lazo;
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