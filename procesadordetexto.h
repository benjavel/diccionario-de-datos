#ifndef PROCESADORDETEXTO_H_INCLUDED
#define PROCESADORDETEXTO_H_INCLUDED

#define ES_VOCAL_TILDE(x) ((x == 'á') || (x=='é') || (x=='í') || (x=='ó') || (x=='ú'))
#define ES_LETRA(x) ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || ES_VOCAL_TILDE(x))
#define ES_BLANCO(x) (x == ' ')
#define ES_SIGNO(x) ((x) == '.' || (x) == ',' || (x) == ';' || (x) == ':' || \
                     (x) == '¡' || (x) == '!' || (x) == '¿' || (x) == '?' || \
                     (x) == '(' || (x) == ')' || (x) == '[' || (x) == ']' || \
                     (x) == '{' || (x) == '}' || (x) == '-' || (x) == '_' || \
                     (x) == '\'' || (x) == '\"' )
#define TAM_LINEA 65536

#include "diccionario.h"
#include <stdio.h>

typedef struct
{
    size_t espacio;
    size_t puntuacion;
    size_t palabras;
}t_contador;

int pasar_texto_a_dic(t_diccionario* dic, const char* nombreArchivo, void (*acumulador)(void**, void*), t_contador* cont);
char* buscarSignoDePuntuacion(char* linea, t_contador* cont);
int esPalabra(char **cad, char **pIni, char **pFin, size_t *cont_blanco, size_t *cont_signo);

#endif
