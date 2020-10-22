#include <stdio.h>
#include <stdlib.h>
#include <string.h>

str_aux apilar(persona p_pila, str_aux ap)
{
    //Reservo el espacio de memoria
    ap.aux = (struct persona_pila *) malloc(sizeof(struct persona_pila));
    if(ap.aux)
    {
        //Cargo los datos
        strcpy(ap.aux->nombre,p_pila.nombre);
        strcpy(ap.aux->apellido,p_pila.apellido);
        ap.aux->edad = p_pila.edad;
        ap.aux->telefono = p_pila.telefono;
        strcpy(ap.aux->mail,p_pila.mail);
        //Hago que el lazo apunte al primero
        ap.aux->lazo = ap.p;
        //El primero apunta al creado
        ap.p = ap.aux;
    } else {
        printf("Memoria insuficiente\n");
    }
    return ap;
}

str_aux escribir(str_aux ap)
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
        ap = apilar(d,ap);
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
    return ap;
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
