#include "uls.h"

void cf_flags_check (t_data *d, bool *fl) {
    if (d){
        cf_not_flag_f(d->files_path, d->files_amt, fl);
        cf_not_flag_f(d->dirs_path, d->dirs_amt, fl);
        cf_flag_S(d->files_path, d->files_amt, fl);
        cf_flag_S(d->dirs_path, d->dirs_amt, fl);
        if (!fl[f]) {
            cf_flag_t(d->files_path, d->files_amt, fl);
            cf_flag_t(d->dirs_path, d->dirs_amt, fl);
            cf_flag_u(d->files_path, d->files_amt, fl);
            cf_flag_u(d->dirs_path, d->dirs_amt, fl);
            cf_flag_c(d->files_path, d->files_amt, fl);
            cf_flag_c(d->dirs_path, d->dirs_amt, fl);
            cf_flag_Uu(d->files_path, d->files_amt, fl);
            cf_flag_Uu(d->dirs_path, d->dirs_amt, fl);
        }
        cf_flag_F_and_p(d->files_path, d->files_amt, fl);
        cf_flag_F_and_p(d->dirs_path, d->dirs_amt, fl);
        cf_flag_r(d->files_path, d->files_amt, fl);
        cf_flag_r(d->dirs_path, d->dirs_amt, fl);
    }
}
