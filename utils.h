#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>
#include "diccionario.h"
#define POS_MAX 5

typedef struct
{
    t_lista *lista;
    int (*cmp)(const void* e1, const void* e2);
} t_parametros_podio;


unsigned long hash_DJB2a(void *str);
int comparar_string(const void* e1, const void* e2);
void imprimir_clavevalor(void* clavevalor, void* params);
void acumular_palabra(void** dest, void* sourc);
void free_clave_valor(void* clavevalor, void* params);
void mostrar_menu();
void pedir_archivo(char* nomArch);
void imprimir_elem_podio(void* info, int pos);
int cmpClaveValor(const void* e1, const void* e2);
void pasarDiccionarioAPodio(void* info, void* params);

#endif
