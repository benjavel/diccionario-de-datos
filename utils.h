#ifndef UTILS_H
#define UTILS_H

#include <string.h>
#include "diccionario.h"


unsigned long hash_DJB2a(unsigned char *str);
int comparar_string(const void* e1, const void* e2);

#endif
