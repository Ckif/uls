#include "uls.h"

int main(int argc, char ** argv) {
//Parsing
    bool *fl = cf_bool_manip(argc, argv);
    t_path *p = wc_getPaths(argc, argv, fl);
//Fetching
    t_data *d = wc_fetchData(p, fl);
//Kostyl dla L
    if (d)
        wc_cutDeadLinks(d->dirs_path, d->dirs_amt, fl);
//Sorting
    cf_flags_check (d, fl);
//Printing
    wc_printResult(d, fl);
//Cleanup
    wc_freePath(p);
    wc_freeData(d);
    free(fl);
    //system("leaks -q uls");
    return fl[err] ? 1 : 0;
}
