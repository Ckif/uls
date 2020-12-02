#include "libmx.h"

void mx_del_strarr(char ***arr) {
    char **buff = *arr;

    for (int i = 0; buff[i] != NULL; i++)
        mx_strdel(&buff[i]);
    free(buff);
    *arr = NULL;
}
