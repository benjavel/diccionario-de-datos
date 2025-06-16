#include <stdio.h>
#include <stdlib.h>
#include "diccionario.h"
#include "utils.h"
#include "procesadordetexto.h"
#include "lista.h"
#include <conio.h>
#define TAM_DICCIONARIO 5

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
    crear_dic(&dic, TAM_DICCIONARIO, hash_DJB2a, comparar_string);
    if(pasar_texto_a_dic(&dic, nomArch, acumular_palabra, &cont) == ERROR)
    {
        printf("Error al procesar el archivo. Asegurate de que el archivo exista y sea legible.\n");
        return 1;
    }

    do
    {
        mostrar_menu();
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1: // Mostrar contador
            printf("Palabras: %d\n", (int)cont.palabras);
            printf("Espacios: %d\n", (int)cont.espacio);
            printf("Signos: %d\n", (int)cont.puntuacion);
            break;
        case 2: // Pedir palabra
            printf("Ingrese la palabra: ");
            char palabra[100];
            int cantApariciones;
            scanf("%s", palabra);
            normalizarClaveMayus(palabra);

            if(obtener_dic(&dic, &palabra, &cantApariciones) == TODO_OK)
            {
                printf("%s ha aparecido %d veces", palabra, cantApariciones);
            }
            else
            {
                printf("\a%s no se encuentra en el texto", palabra);
            }
            break;
        case 3: // Podio
            printf("%-30s | CANTIDAD | PUESTO \n", "PALABRA");

            t_lista podio;
            crear_lista(&podio);
            t_parametros_podio params;
            params.lista = &podio;
            params.cmp = cmpClaveValor;

            recorrer_dic(&dic, pasarDiccionarioAPodio, &params);
            mostrar_podio(&podio, imprimir_elem_podio, cmpClaveValor);

            eliminar_actual_lista(&podio);
            break;
        case 4: // Elegir otro archivo
            pedir_archivo(nomArch);
            vaciar_dic(&dic);
            crear_dic(&dic, TAM_DICCIONARIO, hash_DJB2a, comparar_string);
            pasar_texto_a_dic(&dic, nomArch, acumular_palabra, &cont);
            break;
        case 5: // Recorrer diccionario (Ver hashes y colisiones)
            recorrer_dic(&dic, imprimir_clavevalor, &dic);
            break;
        case 6: // Eliminar palabra
            printf("Elige la palabra a eliminar: ");
            char claveElim[256];
            scanf("%s", claveElim);

            normalizarClaveMayus(claveElim);
            if(sacar_dic(&dic, claveElim))
            {
                printf("Palabra eliminada exitosamente\n");
            }
            else
            {
                printf("Error eliminando la palabra del diccionario");
            }

            break;
        case 7: // Salir
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
    while(opcion != 7);

    vaciar_dic(&dic);

    return 0;
}
