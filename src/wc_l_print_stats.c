#include "uls.h"

static inline void printH(struct stat st) {
    mx_printstr("   ");
    if (st.st_size < 1000) {
        for (int i = 3 - wc_getBitDepth(st.st_size); i > 0; i--)
            mx_printchar(' ');
        mx_printint(st.st_size);
        mx_printchar('B');
    }
    else if (st.st_size >= 1000 && st.st_size < 1000000) {
        wc_printDouble((double)st.st_size / BIBYTE);
        mx_printchar('K');
    }
    else if (st.st_size >= 1000000 && st.st_size < 1000000000) {
        wc_printDouble((double)st.st_size / BIBYTE / BIBYTE);
        mx_printchar('M');
    }
    else if (st.st_size >= 1000000000 && st.st_size < 1000000000000) {
        wc_printDouble((double)st.st_size / BIBYTE / BIBYTE / BIBYTE);
        mx_printchar('G');
    }
}
static inline void printSize(struct stat st, t_lout l, bool *fl) {
    // Column 5 (size)
    if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode) || S_ISSOCK(st.st_mode)) {
        int mjr = major(st.st_rdev);
        int mnr = minor(st.st_rdev);
        //major
        for (int i = l.d_size - wc_getBitDepth(mjr) - 4; i > 0; i--)
            mx_printchar(' ');
        mx_printint(mjr);
        mx_printstr(", ");
        //minor
        for (int i = l.d_size - wc_getBitDepth(mnr) - 6; i > 0; i--)
            mx_printchar(' ');
        if (mnr > 255) {
            char *tmp = mx_nbr_to_hex(mnr);
            write(1, "0x00000000", 10 - mx_strlen(tmp));
            mx_printstr(tmp);
            free(tmp);
        } else {
            mx_printint(mnr);
        }
    }
    else {
        if (fl[h])
            printH(st);
        else {
            for (int i = l.d_size - wc_getBitDepth(st.st_size) + !l.d_minor; i > -1; i--)
                mx_printchar(' ');
            mx_printint(st.st_size);
        }
    }
    mx_printchar(' ');
}
void wc_printStats(struct stat st, t_lout l, bool *fl) {
    struct passwd* tmp = getpwuid(st.st_uid);
    struct group *tmp_g = getgrgid(st.st_gid);

    //Column 2 (links)
    for (int i = l.a_link - wc_getBitDepth(st.st_nlink); i >= 0; i--)
        mx_printchar(' ');
    mx_printint(st.st_nlink);
    //Column 3 (owner)
    if (!fl[g]) {
        mx_printchar(' ');
        if (tmp && !fl[n]) {
            mx_printstr(tmp->pw_name);
            for (int i = l.b_owner - mx_strlen(tmp->pw_name); i > 0; i--)
                mx_printchar(' ');
        } else {
            mx_printint(st.st_uid);
            for (int i = l.b_owner - wc_getBitDepth(st.st_uid); i > 0; i--)
                mx_printchar(' ');
        }
    }
    // Column 4 (group)
    if (!fl[o]) {
        mx_printstr(fl[g] ? " " : "  ");
        if (tmp_g && !fl[n]) {
            mx_printstr(tmp_g->gr_name);
            for (int i = l.c_group - mx_strlen(tmp_g->gr_name); i > 0; i--)
                mx_printchar(' ');
        } else {
            mx_printint(st.st_gid);
            for (int i = l.c_group - wc_getBitDepth(st.st_gid); i > 0; i--)
                mx_printchar(' ');
        }
    }
    mx_printstr(fl[g] && fl[o] ? " " : "");
    printSize(st, l, fl);
}
