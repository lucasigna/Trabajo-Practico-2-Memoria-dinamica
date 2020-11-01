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

typedef struct extraccionRepuestos_str{
    repuestos_t repuesto;
    int cantidad;
    struct extraccionRepuestos_str *lazo;
}extraccionRepuestos_t;

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
                            dia_r = 10*charToInt(r->fecha[0]) + 1*charToInt(r->fecha[1]);
                            mes_r = 10*charToInt(r->fecha[3]) + 1*charToInt(r->fecha[4]);
                            anio_r = 1000*charToInt(r->fecha[6]) + 100*charToInt(r->fecha[7]) + 10*charToInt(r->fecha[8]) + 1*charToInt(r->fecha[9]);
                            hora_r = 10*charToInt(r->hora[0]) + 1*charToInt(r->hora[1]);
                            minuto_r = 10*charToInt(r->hora[3]) + 1*charToInt(r->hora[4]);
                            tiempo_r = 100000000*anio_r + 1000000*mes_r + 10000*dia_r + 100*hora_r + minuto_r;
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
    struct extraccionRepuestos_str *p_ex, *u_ex, *aux_ex, *r_ex;
    p_ex = NULL;
    u_ex = NULL;
    aux_pila = p_pila;
    while(aux_pila)
    {
        int modeloRepetido = 1;
        aux_ex = p_ex;
        while(aux_ex)
        {
            if(strcmp(aux_ex->repuesto->modelo,aux_pila->modelo) == 0)
            {
                aux_ex->cantidad++;
                modeloRepetido = 0;
            }
            aux_ex = aux_ex->lazo;
        }
        if(modeloRepetido)
        {
            aux_ex = (struct extraccionRepuestos_str *) malloc(sizeof(struct extraccionRepuestos_str));
            if(aux_ex)
            {
                strcpy(aux_ex->repuesto->modelo,aux_pila->modelo);
                strcpy(aux_ex->repuesto->cliente,aux_pila>cliente);
                strcpy(aux_ex->repuesto->descripciondeFalla,aux_pila->descripciondeFalla);
                strcpy(aux_ex->repuesto->fecha,aux_pila->fecha);
                strcpy(aux_ex->repuesto->hora,aux_pila->hora);
                aux_ex->repuesto->numeroDeOrden = aux_pila->numeroDeOrden;
                aux_ex->cantidad = 1;
                if(p_ex == NULL)
                {
                    p_ex=u_ex=aux_ex;
                    u_ex->lazo = NULL;
                } else {
                    r_ex = p_ex;
                    if(strcmp(r_ex->repuesto->modelo,aux_ex->repuesto->modelo) > 0)
                    {
                        aux_ex->lazo = p_ex;
                        p_ex = aux_ex;
                    } else {
                        while(ap.r->lazo != NULL && (strcmp(r_ex->lazo->repuesto->modelo,aux_ex->repuesto->modelo) < 0 ))
                        {
                            r_ex = r_ex->lazo;
                        }
                        if(r_ex == u_ex)
                        {
                            u_ex->lazo = aux_ex;
                            u_ex = aux_ex;
                            u_ex->lazo = NULL;
                        } else {
                            aux_ex->lazo = r_ex->lazo;
                            r_ex->lazo = aux_ex;
                        }
                    }
                }
            }
        }
        aux_pila = aux_pila->lazo;
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