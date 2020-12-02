#include "uls.h"

static inline void printDelimiter(int *len, char *name, int win_col) {
    int ln = mx_strlen(name);

    mx_printstr(", ");
    if (((*len) + ln + 4 <= win_col))
        (*len) += 2;
    else if (((*len) + ln + 4 > win_col)) {
        (*len) = 0;
        mx_printchar('\n');
    }
}/*==========================================================================*/
void wc_printWithM(t_obj **fp, int fp_amt, bool *fl) {
    struct winsize w;
    int len = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    w.ws_col = fl[tty] ? 79 : w.ws_col;
    if (mx_strlen(fp[0]->s_name) >= w.ws_col)
        mx_printchar('\n');

    for (int i = 0; i < fp_amt; i++) {
        if (i != 0)
            printDelimiter(&len, fp[i]->s_name, w.ws_col);
        wc_printName(fp[i], fl);
        len += mx_strlen(fp[i]->s_name);
    }
    mx_printstr("\n");
}
