#include "libmx.h"

void mx_str_reverse(char *s) {
    int l = mx_strlen_safe(s) - 1;
    int c = 0;

    while (c < l)
        mx_swap_char(&s[c++],&s[l--]);
}
