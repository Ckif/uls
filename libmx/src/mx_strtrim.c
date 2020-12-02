#include "libmx.h"

char *mx_strtrim(const char *str) {
    int i;
    char * res;

    if(!str)
        return NULL;
    while (mx_isspace(*str))
        str++;  
    i = mx_strlen(str);
    while (mx_isspace(str[i - 1]))
        i--;
    res = mx_strnew(i);
    res = mx_strncpy(res, str, i);
    return res;
}
