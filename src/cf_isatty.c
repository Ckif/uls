#include "uls.h"

bool *cf_isatty(bool *fls) {
    bool *flags = fls;

    if (!isatty(1)) {
        if (flags[l] == false && flags[m] == false &&
            flags[C] == false && flags[one] == false) {
            flags[one] = true;
        }
        flags[G] = false;
        flags[tty] = true;
    }
    return flags;
}
