  
#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    size_t i = 0;

    while (((const unsigned char *)s1)[i] == ((const unsigned char *)s2)[i])
        i++;
    if (i < n)
        return ((const unsigned char *)s1)[i] - ((const unsigned char *)s2)[i];
    return 0;
}
