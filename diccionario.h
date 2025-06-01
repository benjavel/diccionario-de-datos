#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

#include "lista.h"
#include <stdlib.h>

#define TODO_OK 1
#define ERROR 0

/* typedef struct s_nodo {
    void* clave, *valor;
    size_t tamClave, tamValor;
    struct s_nodo* sig;
} t_nodo; */

// typedef struct
// {
//     void* clave, *valor;
//     size_t tamClave, tamValor;
// }t_clave_valor;

typedef struct
{
    void* clave, *valor;
    size_t tamClave, tamValor;
}t_clave_valor;


typedef struct {
    t_lista *buckets; // vector de listas
    size_t capacidad;
    unsigned long (*hash)(void*);
    int (*cmp)(const void *e1, const void *e2);
} t_diccionario;

// /**
// debe recibir por par�metro una capacidad m�xima y definir los valores
// necesarios para inicializar el diccionario.
// */
int crear_dic(t_diccionario *pdic, size_t capacidad, unsigned int (*hash)(void *), int (*cmp)(const void *e1, const void *e2));
// /**
// agrega un nuevo elemento al diccionario. Recibe la clave y el valor a
// agregar al diccionario, calcula la posici�n correcta para insertarlo y maneja las
// colisiones.
// */
// int poner_dic(t_diccionario * pdic, void* clave, void *valor, size_t tamClave, size_t tamValor, void (*acumulador)(void*, void*));

// /**
// busca un elemento en el diccionario por clave y devuelve el valor.
// */
// //int obtener_dic();

// /**
// Elimina un elemento del diccionario buscando por clave.
// */
// //int sacar_dic();

// /**
// Recorre el diccionario de datos ejecutando una acci�n para cada
// elemento presente.
// */
// int recorrer_dic(t_diccionario* pdic, void (*accion)(void*, void*), void* params);

// /**
// Vac�a el diccionario y libera toda la memoria
// */
// int vaciar_dic();

#endif // DICCIONARIO_H_INCLUDED
