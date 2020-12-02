#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *res = NULL;
    char *tmp = NULL;
    int cnt = 0;

    if (!str)
        return NULL;
    tmp = mx_strnew(mx_strlen(str));
    for (int i = 0; str[i] != '\0'; i++) {
        if (!mx_isspace(str[i]))
            tmp[cnt++] = str[i];
        if (!mx_isspace(str[i]) && mx_isspace(str[i + 1]))
            tmp[cnt++] = ' ';
    }
    res = mx_strtrim(tmp);
    mx_strdel(&tmp);
    return res;
}
