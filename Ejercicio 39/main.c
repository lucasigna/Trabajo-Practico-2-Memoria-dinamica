#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dato_str{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    struct dato_str *lazo;
    } dato_t;

typedef struct{
        struct dato_str *p, *u, *aux, *r;
        } str_aux;

str_aux agregar(str_aux ap);
void imprimir(str_aux ap);

int main()
{
    str_aux ap;
    ap.p = NULL;
    ap.u = NULL;
    int op;
    do
    {
        printf("******Menu*******\n");
        printf("1.Agregar un dato\n");
        printf("2.Imprimir y salir\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
                system("cls");
                ap = agregar(ap);
                break;
            case 2:
                system("cls");
                imprimir(ap);
                break;
        }
        system("cls");
    }while(op != 2);
    return 0;
}

str_aux agregar(str_aux ap)
{
    dato_t d;
    printf("Descripción: ");
    scanf("%s",d.desc);
    fflush(stdin);
    printf("Potencia: ");
    scanf("%c",&d.potencia);
    fflush(stdin);
    d.estado = d.desc[0]*d.potencia;
    ap.aux = (struct dato_str *) malloc(sizeof(struct dato_str));
    if(ap.aux)
    {
        strcpy(ap.aux->desc,d.desc);
        ap.aux->potencia = d.potencia;
        ap.aux->estado = d.estado;
        if(ap.p == NULL)
        {
            ap.p=ap.u=ap.aux;
            ap.u->lazo = NULL;
        } else {
            ap.r = ap.p;
            if(ap.r->potencia < ap.aux->potencia)
            {
                ap.aux->lazo = ap.p;
                ap.p = ap.aux;
            } else {
                while(ap.r->lazo)
                {
                    if(ap.r->lazo->potencia > ap.aux->potencia)
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

void imprimir(str_aux ap)
{
    FILE *f;
    f = fopen("potencia.dat","ab");
    ap.aux = ap.p;
    printf(" Estado   Potencia  Descripcion\n\n");
    while(ap.aux)
    {
        ///Guardar registro
        dato_t d;
        strcpy(d.desc,ap.aux->desc);
        d.potencia = ap.aux->potencia;
        d.estado = ap.aux->estado;
        printf("  %-8d  %-8c   %-2s  \n",d.estado,d.potencia,d.desc);
        fwrite(&d,sizeof(d),1,f);
        ap.aux = ap.aux->lazo;
    }
    fclose(f);
    system("pause");
}