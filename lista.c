#include "lista.h"

void crear_lista(t_lista *pl){
    *pl = NULL;
}

void vaciar_lista(t_lista *pl){
    t_nodo *elim;
    while(*pl){
        elim = *pl;
        *pl = elim->sig;
        free(elim->info);
        free(elim);
    }
}

int insertarAlFinalNoDup(t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2), void (*acumulador)(void**, void*))
{
    int rc;

    while (*pl && (rc = cmp(dato, (*pl)->info)) != 0 )
    {
        pl = &(*pl)->sig;
    }

    if(*pl && !rc && acumulador)
    {
        acumulador(&(*pl)->info, dato);
        return DUPLICADO;
    }

    t_nodo* nue = malloc(sizeof(t_nodo));
    if(!nue)
        return ERROR;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return ERROR;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, dato, tam);
    nue->sig = NULL;

    *pl = nue;

    return TODO_OK;
}

int insertarOrdenadoLista(t_lista* pl, const void* dato, size_t tamDato, int(*cmp)(const void* e1, const void* e2))
{
    t_nodo* nuevo;

    while (*pl && cmp((*pl)->info, dato) > 0)
    {
        pl = &(*pl)->sig;
    }

    nuevo = (t_nodo*)malloc(sizeof(t_nodo));
    if(!nuevo)
    {
        return ERROR;
    }
    nuevo->info = malloc(tamDato);
    if(!nuevo->info)
    {
        free(nuevo);
        return ERROR;
    }

    memcpy(nuevo->info, dato, tamDato);
    nuevo->tamInfo = tamDato;
    nuevo->sig = *pl;
    *pl = nuevo;

    return TODO_OK;
}

int buscarEnLista(const t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2))
{
    int resultado;
    while(*pl && (resultado = cmp(dato, (*pl)->info)) != 0){
        pl = &(*pl)->sig;
    }

    if(!*pl || resultado != 0){
        return ERROR;
    }

    memcpy(dato, (*pl)->info, MINIMO((*pl)->tamInfo, tam));
    return TODO_OK;
}

int eliminarDeLista(t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2))
{
    t_nodo *elim;
    int resultado;
    if(!(*pl))
    {
        return LISTA_VACIA;
    }

    while(*pl && (resultado = cmp(dato, (*pl)->info)) !=0)
    {
        pl = &(*pl)->sig;
    }

    if(!(*pl) || resultado != 0)
    {
        return NO_ENCONTRADO;
    }

    memcpy(dato, (*pl)->info, MINIMO((*pl)->tamInfo, tam));

    elim = *pl;
    *pl = elim->sig;
    free(elim->info);
    free(elim);

    return TODO_OK;
}

int eliminar_actual_lista(t_lista *pl)
{

    t_nodo* elim;
    while(*pl)
    {
        elim = *pl;
        *pl = elim->sig;

        free(elim->info);
        free(elim);
    }

    *pl = NULL;

    return TODO_OK;
}


void recorrer_lista(t_lista *pl, void (*accion)(void*, void*), void* params)
{
    while(*pl)
    {
        accion((*pl)->info, params);
        pl = &(*pl)->sig;
    }
}
