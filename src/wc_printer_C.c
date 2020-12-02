#include "uls.h"

static inline int findMaxLenName(t_obj **fp, int fp_amt, bool *fl) {
    int l = mx_strlen(fp[0]->s_name);

    for(int i = 1; i < fp_amt; i++)
        l = l < mx_strlen(fp[i]->s_name) ? mx_strlen(fp[i]->s_name) : l;
    return fl[G] ? l : l - l % 8 + 8;
}/*--------------------------------------------------------------------------*/
static inline void printMultiCols(t_obj **fp, int fp_amt, int max_len, int win,
                                                                    bool *fl) {
    char tab = fl[G] ? ' ' : '\t';
    int cols = win / (max_len + fl[G]);
    int rows = !(fp_amt % cols) ? fp_amt / cols : fp_amt / cols + 1;
    int tmp;

    for (int i = 0; i < rows; mx_printchar(10)) {
        for (int j = i++; j < fp_amt; j += rows) {
                wc_printName(fp[j], fl);
                //mx_printint(mx_strlen(fp[j]->s_name));
                if (fl[G])
                    tmp = (max_len + 1 - mx_strlen(fp[j]->s_name));
                else {
                    tmp = (max_len - mx_strlen(fp[j]->s_name)) / 8;
                    (max_len - mx_strlen(fp[j]->s_name)) % 8 != 0 ? tmp++ : tmp;
                }
                for (int k = 0; k++ < tmp && j + rows < fp_amt; mx_printchar(tab));
        }
    }
}/*--------------------------------------------------------------------------*/
static inline void printInOneRow(t_obj **fp, int fp_amt, int max_len, 
                                                            bool *fl) {
    for (int i = 0; i < fp_amt; i++) {
            wc_printName(fp[i], fl);
            if (i + 1 < fp_amt)
                for (int j = mx_strlen(fp[i]->s_name); j < max_len+fl[G]+(fl[p]||fl[F]); j++)
                    mx_printchar(' ');
    }
    fp_amt > 0 ? mx_printchar(10) : mx_printstr("");
}/*==========================================================================*/
void wc_printWithC(t_obj **fp, int fp_amt, bool *fl) {
    struct winsize w;
    int max_len = findMaxLenName(fp, fp_amt, fl);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    w.ws_col = fl[tty] ? 79 : w.ws_col;

    if (w.ws_col < max_len)
        wc_printWithOne(fp, fp_amt, fl);
    else if (w.ws_col >= max_len * fp_amt)
        printInOneRow(fp, fp_amt, max_len, fl);
    else
        printMultiCols(fp, fp_amt, max_len, w.ws_col, fl);
}

