#include "libmx.h"

int mx_count_words(const char *str, char c) {
    int result = 0;

    if (str == NULL)
        return -1;
    while (*++str)
        result += (*str == c && *(str - 1) != c);
    result += (*(str - 1) != c);
    return result;
}
