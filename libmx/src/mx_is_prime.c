#include "libmx.h"

bool mx_is_prime(int num) {
    if(num <= 1)
        return 0;
    for (int i = 2; i < num; i++) {
        if (!(num % i))
            return 0;
    }
    return 1;
}
