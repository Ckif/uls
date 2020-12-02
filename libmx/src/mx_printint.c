#include "libmx.h"

void mx_printint(int n) {
    unsigned int m = n * (n >= 0) - n * (n < 0);

    if (n < 0) 
        mx_printchar('-');
    if (m / 10)
        mx_printint(m / 10);
    mx_printchar(m % 10 + 48);
}

