#include "uls.h"

static inline void printDog(t_obj *obj) {
    char l[1024];

    if (listxattr(obj->path_name, l, 1024, 1) > 0) {
        mx_printchar('\n');
        ssize_t attr_2 = getxattr(obj->path_name, l, 0, 1024, 0, 1);
        mx_printchar('\t');
        mx_printstr(l);
        mx_printchar('\t');
        mx_printstr("   ");
        mx_printint(attr_2);
        mx_printchar(' ');
    }
}
void wc_printWithL(t_obj **fp, int fp_amt, bool *fl, bool use_total) {
    t_lout spaces = wc_getSizesForL(fp, fp_amt, fl);
    if (use_total) {
        mx_printstr("total ");
        mx_printint(spaces.total);
        mx_printchar('\n');
    }
    for(int i = 0; i < fp_amt; i++) {
        wc_printPerms(fp[i]->st, fp[i]->path_name);
        wc_printStats(fp[i]->st, spaces, fl);
        wc_printTime(fp[i]->st, fl);
        mx_printstr(" ");
        wc_printName(fp[i], fl);
        if (fp[i]->type == lnk) {
            char ln[1024];
            if (fl[F])
                fp[i]->path_name[mx_strlen(fp[i]->path_name) - 1] = '\0';
            int lnl = readlink(fp[i]->path_name, ln, 1024);

            ln[lnl] = '\0';
            mx_printstr(" -> ");
            mx_printstr(ln);
        }
        if (fl[dog])
            printDog(fp[i]);
        mx_printstr("\n");
    }
}
