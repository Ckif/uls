#include "libmx.h"

int mx_strlen_safe(const char *s) {
    int count = 0;

    if (s)
        while (s[count])
            count++;
    return count;
}
