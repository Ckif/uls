#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    char cbuff[100];
    char *result = NULL;
    long rem;
    int i = 0;
    
    if (!nbr) {
        result = mx_strnew(1);
        result[0] = '0';
        return result;
    }
    for (; nbr; nbr = nbr / 16) {
        rem = nbr % 16;
        cbuff[i++] = rem + 48 + 39 * (rem > 9);
    }
    result = mx_strnew(i);
     for(int j = 0; i > 0; i--, j++)
        result[j] = cbuff[i-1];
    return result;
}
