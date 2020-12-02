#include "uls.h"

bool *cf_bool_manip(int argc, char **argv) {
    bool *fls = cf_flags_num (argc, argv);
    fls = cf_cmp_flags(fls);
    fls = cf_isatty(fls);
    return fls;
}
