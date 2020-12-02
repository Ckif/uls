#include "libmx.h"

bool mx_isdigit(int c) {
    if (c > 47 && c < 59)
        return true;
    return false;
}

