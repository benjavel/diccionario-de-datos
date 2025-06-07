#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include <stdio.h>
#include "diccionario.h"


unsigned long hash_DJB2a(void *str);
int comparar_string(const void* e1, const void* e2);
void imprimir_clavevalor(void* clavevalor, void* params);
void acumular_palabra(void** dest, void* sourc);
int mostrar_menu();
int pedir_archivo(char* nomArch);

#endif
