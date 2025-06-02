#include "procesadordetexto.h"


// . ; , ! ¡ ¿ ?
//  calcule la cantidad de palabras, espacios y signos de puntuación que contiene
int pasar_texto_a_dic(t_diccionario* dic, const char* nombreArchivo, void (*acumulador)(void**, void*), t_contador* cont)
{

    char *ptr, *ini, *fin;


    char *puntero;
    char clave[100];
    char linea[TAM_LINEA];
    int valor = 1;
    FILE* pf = fopen(nombreArchivo, "rt");
    if(!pf)
        return ERROR;


    cont->palabras = cont->espacio = cont->puntuacion = 0;

    /* while (fgets(linea, 65536, pf))
    {
        puntero = strchr(linea, '\n');

        while (puntero)
        {
            *puntero = '\0';
            puntero = buscarSignoDePuntuacion(linea, cont);
            if (esPalabra(*puntero, puntero, strchr(puntero, '\0'), &(cont->espacio), &(cont->puntuacion)))
            {
                strcpy(clave, puntero + 1);
                poner_dic(dic, clave, 1, strlen(clave), sizeof(int), acumulador);
                cont->palabras++;
                }

                }

                strcpy(clave, linea);
                poner_dic(dic, clave, 1, strlen(clave), sizeof(int), acumulador);
                cont->palabras++;

                } */

        while (fgets(linea, TAM_LINEA, pf)){ // 2^16
        ptr = linea;
        while( esPalabra(&ptr, &ini, &fin, &(cont->espacio), &(cont->puntuacion)) ){
            memcpy(clave, ini, fin - ini);
            clave[fin - ini] = '\0';
            printf("%s\n", clave);
            cont->palabras++;
            poner_dic(dic, clave, &valor, strlen(clave), sizeof(int), acumulador);

        }
    }

    fclose(pf);
}

char* buscarSignoDePuntuacion(char* linea, t_contador* cont)
{
    char* arraySignos[8] = {'.', ';',',', '!', '¡', '¿', '?', ' '};
    char* mayor;
    int i;

    for (i = 0; i < 8; i++)
    {
        char* caracter = strrchr(linea, arraySignos[i]);
        if (!(*mayor))
        {
            mayor = caracter;
        }
        else if (mayor < caracter)
        {
            mayor = caracter;
        }
        if (caracter == ' ')
            cont->espacio++;
        else
            cont->puntuacion++;
    }

    return mayor;
}

int esPalabra(char **cad, char **pIni, char **pFin, size_t *cont_blanco, size_t *cont_signo){
    char *p = *cad;

    while(*p != '\0') {
        while(ES_BLANCO(*p)){
            p++;
            (*cont_blanco)++;
        }

        while(ES_SIGNO(*p)){
            p++;
            (*cont_signo)++;
        }

        if(ES_LETRA(*p)) {
            break;
        }

        if(*p != '\0' && !ES_BLANCO(*p) && !ES_SIGNO(*p) && !ES_LETRA(*p)) {
            p++;
        }
    }

    if(*p == '\0') {
        *cad = p;
        return 0;
    }

    *pIni = p;

    while(ES_LETRA(*p)){
        p++;
    }

    *pFin = p;
    *cad = p;
    return 1;
}







