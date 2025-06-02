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

    printf("\n[%d] { %s : %d }", indice, (char*)cv->clave, *(int*)cv->valor);

}

void acumular_palabra(void** dest, void* sourc)
{
    t_clave_valor *destClave = *dest;
    t_clave_valor *sourcClave = sourc;

    int* cantidadDest = destClave->valor;
    int* cantidadSourc = sourcClave->valor;

    *cantidadDest += *cantidadSourc;
}
