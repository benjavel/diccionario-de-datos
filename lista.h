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
int insertarAlFinalNoDup(t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2), void (*acumulador)(void**, void*));
int insertarOrdenadoLista(t_lista* pl, const void* dato, size_t tamDato, int(*cmp)(const void* e1, const void* e2));
int buscarEnLista(const t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2));
int eliminarDeLista(t_lista *pl, void* dato, size_t tam, int (*cmp)(const void *e1, const void *e2));
int eliminar_actual_lista(t_lista *pl);
void vaciar_lista(t_lista *pl);
void recorrer_lista(t_lista *pl, void (*accion)(void*, void*), void* params);
int insertarEnPodio(t_lista *pl, void *elem, size_t cantBytes, int (*cmp)(const void *a, const void *b), int n);
void mostrar_podio(const t_lista *pl, void (*mostrar_elemento)(void*, int), int (*cmp)(const void *e1, const void *e2));

#endif