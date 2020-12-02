  
#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *tSrc =(unsigned char *)src;
    unsigned char *tDSt =(unsigned char *)dst;

    if ((tSrc == NULL) &&(tDSt == NULL))
        return NULL;
    if ((tSrc < tDSt) && (tDSt < tSrc + len)) {
        for (tDSt += len, tSrc += len; len--;)
            *(--tDSt) = *(--tSrc);
    }
    else
        while(len--)
            *(tDSt++) = *(tSrc++);
    return dst;
}
