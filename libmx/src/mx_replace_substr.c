#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, 
                        const char *replace) {
    int rlen;
    int slen;
    int i;
    char *res = NULL;
    char *tmp;

    if (!str || !sub || !replace)
        return NULL;
    slen = mx_strlen(sub);
    rlen = mx_strlen(replace);
    res = mx_strnew(mx_strlen(str)+ mx_count_substr(str, sub) * (rlen - slen));
    tmp = res;
    while ((i = mx_get_substr_index(str, sub)) > -1) {
        mx_strncpy(tmp, str, i);
        mx_strcat(tmp, replace);
        tmp += i + rlen;
        str += i + slen;
    }
    mx_strcpy(tmp, str);
    return res;
}
