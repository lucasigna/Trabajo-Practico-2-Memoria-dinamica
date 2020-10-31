#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct repuestos_str{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   struct repuestos_str *lazo, *ant;
}repuestos_t;

int main()
{
    struct repuestos_str *p, *u, *aux;
    p = NULL;
    u = NULL;
    repuestos_t d;
    FILE *f, *fn;
    fn = fopen("stock_nuevo.dat","wb");
    fclose(fn);
    f = fopen("stock.dat","rb");
    fn = fopen("stock_nuevo.dat","ab");
    if(f != NULL && fn != NULL)
    {
        fread(&d,sizeof(d),1,f);
        while(!feof(f))
        {
            if( !(d.partNumber == 1234 && d.serialNumber&(1<<3) && d.serialNumber&(1<<5)) )
            {
                //Guardo la pieza no fallada
                fwrite(&d,sizeof(d),1,fn);
            } else {
                //Pieza fallada, la pongo en la cola
                aux = (struct repuestos_str*) malloc(sizeof(struct repuestos_str));
                if(aux)
                {
                    strcpy(aux->descripcion,d.descripcion);
                    strcpy(aux->ubicacion,d.ubicacion);
                    aux->serialNumber = d.serialNumber;
                    aux->partNumber = d.partNumber;
                    if(p == NULL)
                    {
                        p = aux;
                        u = aux;
                    } else {
                        aux->ant = u;
                        u->lazo = aux;
                        u = aux;
                    }
                    u->lazo = NULL;
                    p->ant = NULL;
                }
            }
            fread(&d,sizeof(d),1,f);
        }
    }
    fclose(f);
    fclose(fn);
    f = fopen("stock.dat","wb");
    fclose(f);
    f = fopen("stock.dat","ab");
    fn = fopen("stock_nuevo.dat","rb");
    if(f != NULL && fn != NULL)
    {
        fread(&d,sizeof(d),1,fn);
        while(!feof(fn))
        {
            fwrite(&d,sizeof(d),1,f);
            fread(&d,sizeof(d),1,fn);
        }
    }
    fclose(f);
    fclose(fn);

    FILE *frev;
    frev = fopen("stock_inverso.dat","wb");
    fclose(frev);
    frev = fopen("stock_inverso.dat","ab");
    aux = u;
    while(aux)
    {
        repuestos_t drev;
        strcpy(drev.descripcion,aux->descripcion);
        strcpy(drev.ubicacion,aux->ubicacion);
        drev.serialNumber = aux->serialNumber;
        drev.partNumber = aux->partNumber;
        fwrite(&drev,sizeof(drev),1,frev);
        aux = aux->ant;
    }
    fclose(frev);
    return 0;
}