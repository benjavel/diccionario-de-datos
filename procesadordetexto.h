#ifndef PROCESADORDETEXTO_H_INCLUDED
#define PROCESADORDETEXTO_H_INCLUDED

#define ES_VOCAL_ACENTUADA_UTF8(p) \
    ((*p == 0xC3) && \
     (*(p+1) == 0xA1 || /* á */ \
      *(p+1) == 0xA9 || /* é */ \
      *(p+1) == 0xAD || /* í */ \
      *(p+1) == 0xB3 || /* ó */ \
      *(p+1) == 0xBA || /* ú */ \
      *(p+1) == 0x81 || /* Á */ \
      *(p+1) == 0x89 || /* É */ \
      *(p+1) == 0x8D || /* Í */ \
      *(p+1) == 0x93 || /* Ó */ \
      *(p+1) == 0x9A||/* Ú */  \
      *(p+1) == 0xB1))
#define ES_LETRA_PTR(p) \
    ((*(p) >= 'a' && *(p) <= 'z') || \
     (*(p) >= 'A' && *(p) <= 'Z') || \
     ES_VOCAL_ACENTUADA_UTF8(p))
#define ES_BLANCO(x) (x == ' ')
#define ES_SIGNO(x) ((x) == '.' || (x) == ',' || (x) == ';' || (x) == ':' || \
                     (x) == 161 || (x) == '!' || (x) == 191 || (x) == '?' || \
                     (x) == '(' || (x) == ')' || (x) == '[' || (x) == ']' || \
                     (x) == '{' || (x) == '}' || (x) == '-' || (x) == '_' || \
                     (x) == '\'' || (x) == '\"' )
#define TAM_LINEA 65536

#include "diccionario.h"
#include <stdio.h>
#include <ctype.h>
//#include <locale.h>

typedef struct
{
    size_t espacio;
    size_t puntuacion;
    size_t palabras;
}t_contador;

int pasar_texto_a_dic(t_diccionario* dic, const char* nombreArchivo, void (*acumulador)(void**, void*), t_contador* cont);
char* buscarSignoDePuntuacion(char* linea, t_contador* cont);
int esPalabra(unsigned char **cad, unsigned char **pIni, unsigned char **pFin, size_t *cont_blanco, size_t *cont_signo);
void normalizarClaveMayus(char* cadena);

#endif
