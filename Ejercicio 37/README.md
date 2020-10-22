# Ejercicio 37
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:
```c
struct d {                                                                                            
long clave; //Clave o Id del registro

char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
```
Se Pide: Realizar una función que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.