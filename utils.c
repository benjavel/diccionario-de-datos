#include "utils.h"

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

    return strncmp((const char*)cv1->clave, (const char*)cv2->clave, cv1->tamClave);
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
    printf("| 6. Eliminar palabra                             |\n");
    printf("| 7. Salir                                        |\n");
    printf("+-------------------------------------------------+\n");
    printf("| Elige una opcion:                               |\n");
    printf("+-------------------------------------------------+\n");

}

void pedir_archivo(char* nomArch)
{

    printf("Ingrese el nombre del archivo que quiere analizar: ");
    scanf("%s", nomArch);
}

void pasarDiccionarioAPodio(void* info, void* params)
{
    t_parametros_podio * parametros = (t_parametros_podio*)params;
    t_clave_valor* cv = (t_clave_valor*)info;
    insertarEnPodio(parametros->lista, cv, sizeof(t_clave_valor), parametros->cmp, POS_MAX);
}

void imprimir_elem_podio(void* info, int pos)
{
    t_clave_valor *a = (t_clave_valor *) info;
    printf("%-30s | %-8d | %d\n", (char *) a->clave, *(int *) a->valor, pos);
}

int cmpClaveValor(const void* e1, const void* e2)
{
    const t_clave_valor* part1 = e1;
    const t_clave_valor* part2 = e2;
    return strcmpi( part1->valor, part2->valor);
}
