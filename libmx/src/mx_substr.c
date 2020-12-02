#include "libmx.h"

char *mx_substr(const char *str, int a, int b) {
    char *tmp;
    int j = 0;

    tmp = mx_strnew(b - a + 1);
    for (int i = a; i < b && str[i] != '\0'; i++) {
        tmp[j] = str[i];
        j++;
    }
    return tmp;
}
