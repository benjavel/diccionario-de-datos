#include "diccionario.h"
#include "utils.h"

int crear_dic(t_diccionario *pdic, size_t capacidad, unsigned long (*hash)(void *), int (*cmp)(const void *e1, const void *e2))
{
    pdic->buckets = (t_lista*)malloc(sizeof(t_nodo *) * capacidad); // tlista??
    if (!pdic->buckets)
    {
        return ERROR;
    }

    pdic->capacidad = capacidad;

    for (int i = 0; i < capacidad; i++)
    {
        crear_lista(&(pdic->buckets[i]));
        // pdic->buckets)[i] = NULL;
    }

    pdic->hash = hash;
    pdic->cmp = cmp;
    return TODO_OK;
}

int poner_dic(t_diccionario *pdic, void *clave, void *valor, size_t tamClave, size_t tamValor, void (*acumulador)(void **, void*))
{
    size_t indice;
    t_clave_valor info;
    //printf("DENTRO DE PONER EN DIC: %s\n", (char*)clave);

    info.clave = malloc(tamClave);
    info.valor = malloc(tamValor);

    memcpy(info.clave, clave, tamClave);
    memcpy(info.valor, valor, tamValor);

    ///info.clave = clave;
    ///info.valor = valor;

    info.tamClave = tamClave;
    info.tamValor = tamValor;

    indice = pdic->hash(clave) % pdic->capacidad;

    return insertarAlFinalNoDup(&(pdic->buckets[indice]), &info, sizeof(t_clave_valor), pdic->cmp, acumulador);
}


int obtener_dic(const t_diccionario *pdic, t_clave_valor *key_val) // preguntar si es valido pasar la estructura
{
    size_t indice = pdic->hash(key_val->clave) % pdic->capacidad;
    return buscarEnLista(&(pdic->buckets[indice]), key_val, sizeof(t_clave_valor),pdic->cmp);
}

int sacar_dic(t_diccionario *pdic, t_clave_valor *key_val)
{
    size_t indice = pdic->hash(key_val->clave) % pdic->capacidad;
    return eliminarDeLista(&(pdic->buckets[indice]), key_val, sizeof(t_clave_valor), pdic->cmp);
}

void recorrer_dic(const t_diccionario *pdic, void (*accion)(void *, void*), void* params)
{

    for (size_t i = 0; i < pdic->capacidad; i++)
    {
        recorrer_lista(&(pdic->buckets[i]), accion, params);
    }

}

void vaciar_dic(t_diccionario *pdic)
{
    for (size_t i = 0; i < pdic->capacidad; i++)
    {
        vaciar_lista(&(pdic->buckets[i])); // cuando i == 0 ???
    }

    pdic->capacidad = 0;
    pdic->cmp = NULL;
    pdic->hash = NULL;
    free(pdic->buckets);
    pdic->buckets = NULL;
}
