#include "diccionario.h"
#include "utils.h"

int crear_dic(t_diccionario *pdic, size_t capacidad, unsigned long (*hash)(void *), int (*cmp)(const void *e1, const void *e2))
{
    pdic->buckets = (t_lista*)malloc(sizeof(t_nodo *) * capacidad); 
    if (!pdic->buckets)
    {
        return ERROR;
    }

    pdic->capacidad = capacidad;

    for (int i = 0; i < capacidad; i++)
    {
        crear_lista(&(pdic->buckets[i]));
    }

    pdic->hash = hash;
    pdic->cmp = cmp;
    return TODO_OK;
}

int poner_dic(t_diccionario *pdic, void *clave, void *valor, size_t tamClave, size_t tamValor, void (*acumulador)(void **, void*))
{
    size_t indice;
    t_clave_valor info;

    info.clave = malloc(tamClave);
    info.valor = malloc(tamValor);

    memcpy(info.clave, clave, tamClave);
    memcpy(info.valor, valor, tamValor);

    info.tamClave = tamClave;
    info.tamValor = tamValor;

    indice = pdic->hash(clave) % pdic->capacidad;

    return insertarAlFinalNoDup(&(pdic->buckets[indice]), &info, sizeof(t_clave_valor), pdic->cmp, acumulador);
}

int obtener_dic(const t_diccionario *pdic, void* clave, void* valor) 
{
    size_t indice = pdic->hash(clave) % pdic->capacidad;
    t_clave_valor* key_val = malloc(sizeof(t_clave_valor));
    if (!key_val)
    {
        return ERROR; // No se pudo asignar memoria
    }

    key_val->clave = clave;
    if(!buscarEnLista(&(pdic->buckets[indice]), key_val, sizeof(t_clave_valor),pdic->cmp))
    {
        return ERROR;   //NO ENCONTRADO
    }

    memcpy(valor, key_val->valor, key_val->tamValor);
    free(key_val);
    return TODO_OK;
}

int sacar_dic(t_diccionario *pdic, void *clave)
{
    size_t indice = pdic->hash(clave) % pdic->capacidad;
    t_clave_valor info;

    info.clave = clave;

    if(eliminarDeLista(&(pdic->buckets[indice]), &info, sizeof(t_clave_valor), pdic->cmp) == TODO_OK)
    {
        free(info.clave);
        free(info.valor);

        return TODO_OK;
    }

    return ERROR;
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
        recorrer_lista(&(pdic->buckets[i]), free_clave_valor, NULL);
        vaciar_lista(&(pdic->buckets[i]));
    }

    pdic->capacidad = 0;
    pdic->cmp = NULL;
    pdic->hash = NULL;
    free(pdic->buckets);
    pdic->buckets = NULL;
}
