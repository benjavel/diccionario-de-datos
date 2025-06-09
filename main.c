#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "utils.h"
#include "procesadordetexto.h"
#include "podio.h"
#include "lista.h"

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
    crear_dic(&dic, 2, hash_DJB2a, comparar_string);
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
            printf("Ingrese la palabra en mayuscula:");
            char palabra[100];
            scanf("%s", palabra);

            t_clave_valor cv;
            cv.tamClave = strlen(palabra) + 1;
            cv.clave = malloc(cv.tamClave);
            normalizarClaveMayus(palabra);
            memcpy(cv.clave, palabra, cv.tamClave);
            cv.valor = NULL;

            if(obtener_dic(&dic, &cv) == TODO_OK)
            {
                printf("%s ha aparecido %d veces", (char*)cv.clave, *(size_t*)cv.valor);
            }
            else
            {
                printf("%s no se encuentra en el texto", (char*)cv.clave);
            }
            break;
        case 3: // Podio
            //printf("PODIO DE LAS 5 PALABRAS CON MAS APARICIONES:\n");
            printf("PUESTO | HASH | %-30s | CANTIDAD |\n", "PALABRA");
            tPodio podio;
            crear_lista(&podio);
            t_parametros_podio params;
            params.podio = &podio;
            params.cmp = compararElementos;
            recorrer_dic(&dic, pasarDiccionarioAPodio, &params);

            recorrer_lista(&podio, imprimir_elem_podio, &dic);

            eliminar_actual_lista(&podio);
            break;
        case 4: // Elejir otro
            pedir_archivo(nomArch);
            vaciar_dic(&dic);
            crear_dic(&dic, 2, hash_DJB2a, comparar_string);
            pasar_texto_a_dic(&dic, nomArch, acumular_palabra, &cont);
            break;
        case 5: //
            recorrer_dic(&dic, imprimir_clavevalor, &dic);
            break;
        case 6: // Salir
            printf("Gracias por usar el diccionario de datos.");
            vaciar_dic(&dic);
            break;
        default:
            printf("Elegi una opcion valida!");
            break;

        }
        getch();
        system("cls || clear");

    }
    while(opcion != 5);

    vaciar_dic(&dic);

    return 0;
}
