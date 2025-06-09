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
