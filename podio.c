#include "podio.h"

// int insertarEnPodio(tPodio* podio, const void* dato, size_t tamDato, float puntaje, int(*cmp)(const void* e1, const void* e2))
// int insertarEnPodio(void* podio, void* params)
// void (*accion)(void*, void*)
void pasarDiccionarioAPodio(void* info, void* params)
{
    t_parametros_podio * parametros = (t_parametros_podio*)params;
    t_clave_valor* cv = (t_clave_valor*)info;

    insertarEnPodio(parametros->podio, cv->clave, cv->tamClave, *(size_t*)cv->valor, parametros->cmp);
}


void pasarDiccionarioAPodio2(void* info, void* params)
{
    t_parametros_podio * parametros = (t_parametros_podio*)params;
    t_clave_valor* cv = (t_clave_valor*)info;
    insertarEnPodio2(parametros->podio, cv, sizeof(t_clave_valor), parametros->cmp, POS_MAX);
}

int insertarEnPodio(tPodio* podio, const void* dato, size_t tamDato, size_t puntaje, int(*cmp)(const void* e1, const void* e2))
{
    tElemPodio nuevoElem;
    nuevoElem.info = malloc(tamDato);

    memcpy(nuevoElem.info, dato, tamDato);
    nuevoElem.tamInfo = tamDato;
    nuevoElem.puntaje = puntaje;
    nuevoElem.posicion = 0;

    if(!insertarOrdenadoLista(podio, &nuevoElem, sizeof(tElemPodio), cmp))
    {
        free(nuevoElem.info);
        return ERR_MEM;
    }

    asignarPosiciones(podio);

    return TODO_OK;
}

void asignarPosiciones(tPodio* podio)
{
    t_lista actual = *podio;
    t_lista anterior = NULL;
    size_t posicion = 1;
    size_t puntajeAnterior = -1;
    size_t cantidadEnPosicion = 0;

    while (actual) {
        tElemPodio* elem = (tElemPodio*)actual->info;

        if (elem->puntaje != puntajeAnterior) {
            posicion += cantidadEnPosicion;
            cantidadEnPosicion = 1;
            puntajeAnterior = elem->puntaje;
        } else {
            cantidadEnPosicion++;
        }

        elem->posicion = posicion;

        if (posicion > POS_MAX)
        {
            if (anterior) //corto la conexion desde el que tiene posicion < 5
            {
                anterior->sig = NULL;
            }
            else
            {
                *podio = NULL;
            }
            eliminar_actual_lista(&actual);
            break;
        }

        anterior = actual;
        actual = actual->sig;
    }
}

int compararElementos(const void* e1, const void* e2)
{
    const tElemPodio* part1 = e1;
    const tElemPodio* part2 = e2;

    return part1->puntaje - part2->puntaje;
}

int cmpClaveValor(const void* e1, const void* e2)
{
    const t_clave_valor* part1 = e1;
    const t_clave_valor* part2 = e2;
    return strcmpi( part1->valor, part2->valor);
}



int insertarEnPodio2(t_lista *pl, void *elem, size_t cantBytes, int (*cmp)(const void *a, const void *b), int n)
{
    int r = 0, ce = 0;
    t_nodo *menor, *elim, *nue;

    while(*pl && (r = cmp((*pl)->info, elem)) >= 0)
    {
        pl = &(*pl)->sig;
        ce++;
    }

    /// no inserto
    if(r != 0 && ce >= n)
    {
        return 3;
    }

    nue = malloc(sizeof(t_nodo));
    if(!nue)
    {
        return ERROR;
    }
    nue->info = malloc(cantBytes);
    if(!nue->info)
    {
        free(nue);
        return ERROR;
    }

    memcpy(nue->info, elem, cantBytes);
    nue->tamInfo = cantBytes;
    nue->sig = *pl;
    *pl = nue;
    t_nodo **act = pl;
    act = &(*act)->sig;
    ce += 2;

    while (*act && ce < n)
    {
        ce++;
        act = &(*act)->sig;
    }

    menor = *act;
    if( ce <= n ){
        while(*act && (r = cmp((*act)->info, menor->info)) == 0)
        {
            act = &(*act)->sig;
        }
    }

    while(*act)
    {
        elim = *act;
        *act = elim->sig;
        free(elim->info);
        free(elim);
    }

    return TODO_OK;

}

