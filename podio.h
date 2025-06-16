#ifndef PODIO_H
#define PODIO_H

#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "diccionario.h"

#define PODIO_VACIO 0
#define ERR_MEM -1

#define POS_MAX 5

typedef t_lista tPodio;
typedef struct
{
    tPodio* podio;
    int (*cmp)(const void* e1, const void* e2);
}t_parametros_podio;

typedef struct
{
    void* info;
    size_t tamInfo;
    size_t puntaje;
    size_t posicion;
}tElemPodio;


int insertarEnPodio(tPodio* podio, const void* dato, size_t tamDato, size_t puntaje, int(*cmp)(const void* e1, const void* e2));
void asignarPosiciones(tPodio* podio);
int compararElementos(const void* e1, const void* e2);
void pasarDiccionarioAPodio(void* info, void* params);
void pasarDiccionarioAPodio2(void* info, void* params);
int cmpClaveValor(const void* e1, const void* e2);

int insertarEnPodio2(t_lista *pl, void *elem, size_t cantBytes, int (*cmp)(const void *a, const void *b), int n);
#endif
