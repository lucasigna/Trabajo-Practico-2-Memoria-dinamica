#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct repuestos_str{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
   struct repuestos_str *lazo;
}repuestos_t;

int charToInt(char a);

int main()
{
    struct repuestos_str *p, *u, *aux, *r, *p_pila, *aux_pila;
    p_pila = NULL;
    p = NULL;
    u = NULL;
    repuestos_t d;
    FILE *f;
    f = fopen("ordenes.dat","rb");
    if(f != NULL)
    {
        fread(&d,sizeof(d),1,f);
        while(!feof(f))
        {
            unsigned long long dia,mes,anio,hora,minuto,dia_r,mes_r,anio_r,hora_r,minuto_r, tiempo_r, tiempo;
            dia = 10*charToInt(d.fecha[0]) + 1*charToInt(d.fecha[1]);
            mes = 10*charToInt(d.fecha[3]) + 1*charToInt(d.fecha[4]);
            anio = 1000*charToInt(d.fecha[6]) + 100*charToInt(d.fecha[7]) + 10*charToInt(d.fecha[8]) + 1*charToInt(d.fecha[9]);
            hora = 10*charToInt(d.hora[0]) + 1*charToInt(d.hora[1]);
            minuto = 10*charToInt(d.hora[3]) + 1*charToInt(d.hora[4]);
            tiempo = 100000000*anio + 1000000*mes + 10000*dia + 100*hora + minuto;

            aux = (struct repuestos_str *) malloc(sizeof(struct repuestos_str));
            if(aux)
            {
                strcpy(aux->fecha,d.fecha);
                strcpy(aux->hora,d.hora);
                strcpy(aux->cliente,d.cliente);
                strcpy(aux->descripciondeFalla,d.descripciondeFalla);
                strcpy(aux->modelo,d.modelo);
                aux->numeroDeOrden = d.numeroDeOrden;
                if(p == NULL)
                {
                    p=u=aux;
                    u->lazo = NULL;
                } else {
                    r = p;
                    dia_r = 10*charToInt(r->fecha[0]) + 1*charToInt(r->fecha[1]);
                    mes_r = 10*charToInt(r->fecha[3]) + 1*charToInt(r->fecha[4]);
                    anio_r = 1000*charToInt(r->fecha[6]) + 100*charToInt(r->fecha[7]) + 10*charToInt(r->fecha[8]) + 1*charToInt(r->fecha[9]);
                    hora_r = 10*charToInt(r->hora[0]) + 1*charToInt(r->hora[1]);
                    minuto_r = 10*charToInt(r->hora[3]) + 1*charToInt(r->hora[4]);
                    tiempo_r = 100000000*anio_r + 1000000*mes_r + 10000*dia_r + 100*hora_r + minuto_r;
                    if(tiempo_r > tiempo)
                    {
                        aux->lazo = p;
                        p = aux;
                    } else {
                        while(r->lazo != NULL && tiempo_r < tiempo)
                        {
                            r = r->lazo;
                            if(r->lazo)
                            {
                                dia_r = 10*charToInt(r->lazo->fecha[0]) + 1*charToInt(r->lazo->fecha[1]);
                                mes_r = 10*charToInt(r->lazo->fecha[3]) + 1*charToInt(r->lazo->fecha[4]);
                                anio_r = 1000*charToInt(r->lazo->fecha[6]) + 100*charToInt(r->lazo->fecha[7]) + 10*charToInt(r->lazo->fecha[8]) + 1*charToInt(r->lazo->fecha[9]);
                                hora_r = 10*charToInt(r->lazo->hora[0]) + 1*charToInt(r->lazo->hora[1]);
                                minuto_r = 10*charToInt(r->lazo->hora[3]) + 1*charToInt(r->lazo->hora[4]);
                                tiempo_r = 100000000*anio_r + 1000000*mes_r + 10000*dia_r + 100*hora_r + minuto_r;
                            }
                        }
                        if(r == u)
                        {
                            u->lazo = aux;
                            u = aux;
                            u->lazo = NULL;
                        } else {
                            aux->lazo = r->lazo;
                            r->lazo = aux;
                        }
                    }
                }
            }
            fread(&d,sizeof(d),1,f);
        }
    }
    fclose(f);
    aux = p;
    while(aux)
    {
        aux_pila = (struct repuestos_str *) malloc(sizeof(struct repuestos_str));
        if(aux_pila)
        {
            strcpy(aux_pila->fecha,aux->fecha);
            strcpy(aux_pila->hora,aux->hora);
            strcpy(aux_pila->cliente,aux->cliente);
            strcpy(aux_pila->descripciondeFalla,aux->descripciondeFalla);
            strcpy(aux_pila->modelo,aux->modelo);
            aux_pila->numeroDeOrden = aux->numeroDeOrden;
            aux_pila->lazo = p_pila;
            p_pila = aux_pila;
        } else {
            printf("Memoria insuficiente\n");
        }
        aux = aux->lazo;
    }
    return 0;
}

int charToInt(char a)
{
    switch(a)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
    }
}