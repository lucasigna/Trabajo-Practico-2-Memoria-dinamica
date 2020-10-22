#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "funciones.c"

int main()
{
    str_aux ap;
    ap.p = NULL;
    ap.u = NULL;
    leerArchivo(ap);
    return 0;
}


