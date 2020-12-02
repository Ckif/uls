#include"uls.h"

void cf_flag_r(t_obj **d, int d_amt, const bool *fl) {
    t_obj *buf;

    if (fl[r]) {
        for(int i = 0, j = d_amt - 1; i < j; i++, j--) {
            buf = d[i];
            d[i] = d[j];
            d[j] = buf;
        }
        for (int i = 0; i < d_amt; i++)
            if (d[i]->kids_amt)
                cf_flag_r(d[i]->kids, d[i]->kids_amt, fl);
    }
}
