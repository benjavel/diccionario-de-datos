#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "utils.h"
#include "procesadordetexto.h"

int main()
{
    printf("  ____  _          _                        _       \n");
    printf(" |  _ \\(_) ___ ___(_) ___  _ __   __ _ _ __(_) ___  \n");
    printf(" | | | | |/ __/ __| |/ _ \\| '_ \\ / _` | '__| |/ _ \\ \n");
    printf(" | |_| | | (_| (__| | (_) | | | | (_| | |  | | (_) |\n");
    printf(" |____/|_|\\___\\___|_|\\___/|_| |_|\\__,_|_|  |_|\\___/ \n");

    int opcion;
    char nomArch[256];

    pedir_archivo(nomArch);

    t_diccionario dic;
    t_contador cont;
    crear_dic(&dic, 500, hash_DJB2a, comparar_string);
    pasar_texto_a_dic(&dic, nomArch, acumular_palabra, &cont);
    do
    {
        mostrar_menu();
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1: // mostrar contador
            printf("Palabras: %d\n", cont.palabras);
            printf("Espacios: %d\n", cont.espacio);
            printf("Signos: %d\n", cont.puntuacion);
            break;
        case 2: // Pedir palabra
            printf("Ingrese la palabra:");
            char palabra[100];
            scanf("%s", palabra);

            t_clave_valor cv;
            cv.tamClave = strlen(palabra) + 1;
            cv.clave = malloc(cv.tamClave);
            memcpy(cv.clave, palabra, cv.tamClave);

            obtener_dic(&dic, &cv);
            printf("%s ha aparecido %d veces", (char*)cv.clave, *(size_t*)cv.valor);
            break;
        case 3: // Podio
            printf("Accion 3");
            break;
        case 4: // Elejir otro
            pedir_archivo(nomArch);
            vaciar_dic(&dic);
            pasar_texto_a_dic(&dic, nomArch, acumular_palabra, &cont);
            break;
        case 5: // Salir
            printf("Gracias por usar el diccionario de datos.");
            vaciar_dic(&dic);
            break;
        default:
            printf("Eleji una opcion valida!");
            break;

        }
        getch();

        system("cls || clear");
    }
    while(opcion != 5);



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
