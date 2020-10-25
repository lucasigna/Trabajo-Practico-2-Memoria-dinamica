#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dato_str{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
    struct dato_str *lazo;
    } dato_t;

struct pot{
    unsigned char potencia;
    struct pot *lazo;
    };

typedef struct{
        struct pot *p, *aux;
        } str_aux;

str_aux buscar(str_aux ap);

int main()
{
    str_aux ap;
    ap.p = NULL;
    int op;
    do
    {
        printf("******Menu*******\n");
        printf("1.Buscar dato\n");
        printf("2.Salir\n");
        scanf("%d",&op);
        fflush(stdin);
        switch(op)
        {
            case 1:
                system("cls");
                ap = buscar(ap);
                break;
        }
        system("cls");
    }while(op != 2);
    return 0;
}


str_aux buscar(str_aux ap)
{
    int id,i = 0,k;
    char c = ' ', *p;
    dato_t d;
    printf("Id: ");
    scanf("%d",&id);
    fflush(stdin);
    FILE *f;
    f = fopen("potencia.dat","rb+");
    fseek(f,(1L)*sizeof(struct dato_str)*(id-1),0);
    fread(&d,sizeof(d),1,f);
    //Obtengo el puntero final
    while(c != '\0')
    {
        c = d.desc[i];
        p = &d.desc[i];
        i++;
    }
    //Imprimo la palabra al reves
    for(k = 0 ; k<(i-1) ; k++)
    {
        p--;
        printf("%c",*p);
    }
    printf("\n");
    //Cambio el bit 3
    d.estado = d.estado^(1<<3);
    fseek(f,-(1L)*sizeof(struct dato_str),0);
    fwrite(&d,sizeof(d),1,f);
    fclose(f);
    if(d.estado&(1<<0) && d.estado&(1<<2))
    {
        //Lo agregó a la pila de potencia
        ap.aux = (struct pot *) malloc(sizeof(struct pot));
        if(ap.aux)
        {
            ap.aux->potencia = d.potencia;
            ap.aux->lazo = ap.p;
            ap.p = ap.aux;
        } else {
            printf("Memoria insuficiente\n");
        }
    } else {
        //Lo subo al archivo nuevo
        FILE *f2;
        f2 = fopen("salida.dat","ab");
        fwrite(&d,sizeof(d),1,f2);
        fclose(f2);
    }
    system("pause");
    return ap;
}