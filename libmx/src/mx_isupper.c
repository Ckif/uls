#include <stdbool.h>

bool mx_isupper(int c) {
    if (c > 64 && c < 91)
        return true;
    return false;
}

