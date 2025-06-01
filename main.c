#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "utils.h"

int main()
{
    printf("Diccionario de datos:");

    t_diccionario dic;
    crear_dic(&dic, 1000, hash_DJB2a, comparar_string);


    char* clave = "CLAVE";
    char* valor = "valor";
    poner_dic(&dic, clave, valor, 6, 6, NULL);

    t_clave_valor cv;
    cv.clave = clave;
    cv.tamClave = 6;
    sacar_dic(&dic, &cv);

    printf("\nClave: %s, Valor: %s", cv.clave, cv.valor);

    return 0;
}
