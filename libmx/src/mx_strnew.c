#include "libmx.h"

char *mx_strnew(const int size) {
    char *str = NULL;

    if (size < 0)
        return NULL;
    str = (char *)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i < size + 1; i++)
        str[i] = '\0';
    return str;
}
