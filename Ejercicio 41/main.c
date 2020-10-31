#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct repuestos_str{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   struct repuestos_str *lazo;
}repuestos_t;

typedef struct{
        struct repuestos_str *p, *u, *aux, *r;
        } str_aux;

str_aux cargar(str_aux ap);
void guardar(str_aux ap);

int main()
{
    str_aux ap;
    ap.p = NULL;
    ap.u = NULL;
    int op;
    do
    {
        printf("******Menu*******\n");
        printf("1.Cargar repuesto\n");
        printf("2.Guardar y salir\n");
        scanf("%d",&op);
        fflush(stdin);
        switch(op)
        {
            case 1:
                system("cls");
                ap = cargar(ap);
                break;
            case 2:
                system("cls");
                guardar(ap);
                break;
        }
        system("cls");
    }while(op != 2);
    return 0;
}

str_aux cargar(str_aux ap)
{
    repuestos_t repuesto;
    printf("Numero de pieza: ");
    scanf("%ld",&repuesto.partNumber);
    fflush(stdin);
    printf("Numero de serie: ");
    scanf("%ld",&repuesto.serialNumber);
    fflush(stdin);
    printf("Descripcion: ");
    scanf("%s",repuesto.descripcion);
    fflush(stdin);
    printf("Ubicación: ");
    scanf("%s",repuesto.ubicacion);
    fflush(stdin);
    ap.aux = (struct repuestos_str *) malloc(sizeof(struct repuestos_str));
    if(ap.aux)
    {
        strcpy(ap.aux->descripcion,repuesto.descripcion);
        strcpy(ap.aux->ubicacion,repuesto.ubicacion);
        ap.aux->serialNumber = repuesto.serialNumber;
        ap.aux->partNumber = repuesto.partNumber;
        if(ap.p == NULL)
        {
            ap.p=ap.u=ap.aux;
            ap.u->lazo = NULL;
        } else {
            ap.r = ap.p;
            if(strcmp(ap.r->descripcion,ap.aux->descripcion) > 0)
            {
                ap.aux->lazo = ap.p;
                ap.p = ap.aux;
            } else {
                while(ap.r->lazo != NULL && (strcmp(ap.r->lazo->descripcion,ap.aux->descripcion) < 0 ))
                {
                    ap.r = ap.r->lazo;
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
    system("cls");
    ap.aux = ap.p;
    printf("\n");
    printf("Nro de serie    Nro de pieza   Descripcion    Ubicacion\n");
    while(ap.aux)
    {
        repuestos_t d;
        strcpy(d.descripcion,ap.aux->descripcion);
        strcpy(d.ubicacion,ap.aux->ubicacion);
        d.serialNumber = ap.aux->serialNumber;
        d.partNumber = ap.aux->partNumber;
        printf("%-11ld     %-8ld       %-8s       %-8s\n",d.serialNumber,d.partNumber,d.descripcion,d.ubicacion);
        ap.aux = ap.aux->lazo;
    }
    system("pause");
    return ap;
}

void guardar(str_aux ap)
{
    FILE *f;
    f = fopen("stock.dat","ab");
    ap.aux = ap.p;
    while(ap.aux)
    {
        repuestos_t d;
        strcpy(d.descripcion,ap.aux->descripcion);
        strcpy(d.ubicacion,ap.aux->ubicacion);
        d.serialNumber = ap.aux->serialNumber;
        d.partNumber = ap.aux->partNumber;
        fwrite(&d,sizeof(d),1,f);
        ap.aux = ap.aux->lazo;
    }
    fclose(f);
}