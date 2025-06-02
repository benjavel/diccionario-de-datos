#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "utils.h"
#include "procesadordetexto.h"

int main()
{
    printf("Diccionario de datos:");
    t_diccionario dic;
    t_contador cont;
    crear_dic(&dic, 500, hash_DJB2a, comparar_string);
    pasar_texto_a_dic(&dic, "test.txt", acumular_palabra, &cont);

    //printf("Cant palabras: %d \nCant Espacios: %d\n Cant Puntuaciones: %d\n", cont.palabras, cont.espacio, cont.puntuacion);

    // char* clave = "Perro";
    // char* valor = "Un perro";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);

    // clave = "Gato";
    // valor = "Un Gato";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);

    // clave = "Otro gato";
    // valor = "Dos gatos";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);

    // clave = "Loro";
    // valor = "Un loro";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);

    // clave = "Iguana";
    // valor = "Una iguana";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);
    // clave = "Manzana";
    // valor = "Una manzana";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);
    // clave = "manzana";
    // valor = "Una manzana (min)";
    // poner_dic(&dic, clave, valor, strlen(clave), strlen(valor), NULL);

    recorrer_dic(&dic, imprimir_clavevalor, &dic);
    // t_clave_valor cv;
    // cv.clave = clave;
    // cv.tamClave = 6;
    // sacar_dic(&dic, &cv);

    // printf("\nClave: %s, Valor: %s", (char*)cv.clave, (char*)cv.valor);

    vaciar_dic(&dic);

    return 0;
}
