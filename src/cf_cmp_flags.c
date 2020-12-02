#include "uls.h"

bool * cf_cmp_flags(bool *fls) {
    bool *flags = fls;
    if (flags[f] == true) {
        flags[a] = true;
        flags[S] = false;
        flags[r] = false;
    }
    if (flags[S] == true)
        flags[t] = false;
    if (flags[a] == true)
        flags[A] = false;
    if (flags[m] == true)
        flags[C] = false;
    if (flags[n] == true || flags[g] || flags[o]) 
        flags[l] = true;
    return flags;
}
