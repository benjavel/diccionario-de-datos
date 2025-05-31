#include "utils.h"

unsigned long hash_DJB2a(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int comparar_string(const void* e1, const void* e2)
{
    const t_clave_valor* cv1 = (const t_clave_valor*)e1;
    const t_clave_valor* cv2 = (const t_clave_valor*)e2;

    if (cv1->tamClave != cv2->tamClave) {
        return (int)(cv1->tamClave - cv2->tamClave);
    }

    return strncmp((const char*)cv1->clave, (const char*)cv2->clave, cv1->tamClave);
}
