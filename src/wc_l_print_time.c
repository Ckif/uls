#include "uls.h"

void wc_printTime(struct stat st, bool *fl) {
   time_t sec = time(NULL);
    time_t time = 0;
    char *sub;
    char *tmp;
    char *tmp_2;

    time = fl[c] ? st.st_ctime : 
            fl[u] ? st.st_atime : 
            fl[U] ? st.st_birthtime : st.st_mtime;
    if (((sec - (time)) > 15778368)) {
        sub = mx_substr(ctime(&(time)), 4, 10);
        tmp = mx_strjoin(sub, "  ");
        free(sub);
        tmp_2 = mx_substr(ctime(&(time)), 20, 24);
        sub = mx_strjoin(tmp, tmp_2);
        free(tmp_2);
        free(tmp);
        mx_printstr(sub);
    }
    else {
        sub = mx_substr(ctime(&(time)), 4, fl[T] ? 24 : 16); 
        mx_printstr(sub);
    }
    free(sub);
}/*==========================================================================*/

