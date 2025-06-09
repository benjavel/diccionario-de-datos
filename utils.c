#include "utils.h"

// Normalizar texto antes de mandarlo al DIC? sí
// tam clave???

unsigned long hash_DJB2a(void *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *(char*)str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int comparar_string(const void* e1, const void* e2)
{
    const t_clave_valor* cv1 = (const t_clave_valor*)e1;
    const t_clave_valor* cv2 = (const t_clave_valor*)e2;

    // if (cv1->tamClave != cv2->tamClave) {
    //     return (int)(cv1->tamClave - cv2->tamClave);
    // }

    return strncmp((const char*)cv1->clave, (const char*)cv2->clave, cv1->tamClave);
    //return strcmpi((const char*)cv1->clave, (const char*)cv2->clave);
}

void imprimir_clavevalor(void* clavevalor, void* params)
{
    t_clave_valor* cv = clavevalor;
    t_diccionario *dic = params;
    int indice = dic->hash(cv->clave) % dic->capacidad;

    printf("\n[%5d] { %-20s : %-2d }", indice, (char*)cv->clave, *(int*)cv->valor);

}

void acumular_palabra(void** dest, void* sourc)
{
    t_clave_valor *destClave = *dest;
    t_clave_valor *sourcClave = sourc;

    int* cantidadDest = destClave->valor;
    int* cantidadSourc = sourcClave->valor;

    *cantidadDest += *cantidadSourc;
}




void free_clave_valor(void* clavevalor, void* params)
{
    t_clave_valor* cv = clavevalor;

    cv->tamClave = 0;
    cv->tamValor = 0;

    free(cv->clave);
    free(cv->valor);
    cv->clave = NULL;
    cv->valor = NULL;
}

void mostrar_menu()
{

    printf("\n+-------------------------------------------------+\n");
    printf("| MENU PRINCIPAL                                  |\n");
    printf("+-------------------------------------------------+\n");
    printf("| 1. Cantidad de palabras, espacios y signos      |\n");
    printf("| 2. Cantidad de apariciones de una misma palabra |\n");
    printf("| 3. Podio                                        |\n");
    printf("| 4. Elegir otro archivo                          |\n");
    printf("| 5. Ver diccionario                              |\n");
    printf("| 6. Salir                                        |\n");
    printf("+-------------------------------------------------+\n");
    printf("| Elige una opcion:                               |\n");
    printf("+-------------------------------------------------+\n");

}

void pedir_archivo(char* nomArch)
{

    printf("Ingrese el nombre del archivo que quiere analizar: ");
    scanf("%s", nomArch);
}


void imprimir_elem_podio(void* info, void* params)
{
    tElemPodio* elemActual = info;
    char* palabraActual = elemActual->info;
    t_diccionario* dic = (t_diccionario*)params;

    int hash = dic->hash(palabraActual) % dic->capacidad;
    printf("%-6d | %-4d | %-30s | %-8d |\n", (int)elemActual->posicion, hash, palabraActual, elemActual->puntaje);
    //printf("%d | [%d] { %s : %d} \n", (int)elemActual->posicion, hash, palabraActual, elemActual->puntaje);
    // printf("Palabra: %s\nCantidad:%.2f\nPuesto %d\n\n", palabraActual, elemActual->puntaje, (int)elemActual->posicion);
}
