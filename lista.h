#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#define ERROR 0
#define ENCONTRADO 0
#define TODO_OK 1
#define NO_ENCONTRADO -1
#define DUPLICADO -2
#define LISTA_VACIA -3

#define MINIMO(a,b)((a)<(b)?(a):(b))

typedef struct s_nodo {
    void* info;
    size_t tamInfo;
    struct s_nodo* sig;
} t_nodo;

typedef t_nodo* t_lista;

void crear_lista(t_lista *pl);
int insertarAlFinalNoDup(t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2), void (*acumulador)(void *, void*));
int buscarEnLista(const t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2));
int eliminarDeLista(const t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2));
void vaciar_lista(t_lista *pl);

#endif