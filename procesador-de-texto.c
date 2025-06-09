#include "procesadordetexto.h"


// . ; , ! ¡ ¿ ?
//  calcule la cantidad de palabras, espacios y signos de puntuación que contiene
int pasar_texto_a_dic(t_diccionario* dic, const char* nombreArchivo, void (*acumulador)(void**, void*), t_contador* cont)
{
    unsigned char *ptr, *ini, *fin;

    unsigned char clave[100];
    unsigned char linea[TAM_LINEA];
    int valor = 1;
    FILE* pf = fopen(nombreArchivo, "rt");
    if(!pf)
        return ERROR;

    cont->palabras = cont->espacio = cont->puntuacion = 0;

    while (fgets((char*)linea, TAM_LINEA, pf)){ // 2^16
        ptr = linea;
        while( esPalabra(&ptr, &ini, &fin, &(cont->espacio), &(cont->puntuacion)) ){
            memcpy(clave, ini, fin - ini);
            clave[fin - ini] = '\0';

            cont->palabras++;

            normalizarClaveMayus((char*)clave);
            poner_dic(dic, clave, &valor, strlen((char*)clave)+1, sizeof(int), acumulador);

        }
    }

    fclose(pf);

    return TODO_OK;
}

int esPalabra(unsigned char **cad, unsigned char **pIni, unsigned char **pFin, size_t *cont_blanco, size_t *cont_signo){
    unsigned char *p = *cad;
    while(*p != '\0') {
        while(ES_BLANCO(*p)){
            p++;
            (*cont_blanco)++;
        }

        while(ES_SIGNO(*p)){
            p++;
            (*cont_signo)++;
        }

        if(ES_LETRA_PTR(p)) {
            break;
        }

        if(*p != '\0' && !ES_BLANCO(*p) && !ES_SIGNO(*p) && !ES_LETRA_PTR(p)) {
            p++;
        }
    }

    if(*p == '\0') {
        *cad = p;
        return 0;
    }

    *pIni = p;


    while (ES_LETRA_PTR(p))
    {
        if(ES_VOCAL_ACENTUADA_UTF8(p))
            p += 2; // Saltar 2 bytes para UTF-8
        else
            p++;
    }

    *pFin = p;
    *cad = p;
    return 1;
}

void normalizarClaveMayus(char* cadena)
{
    while(*cadena != '\0')
    {
        *cadena = toupper(*cadena);
        cadena++;
    }
}
