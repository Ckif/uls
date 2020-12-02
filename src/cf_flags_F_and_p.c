#include "uls.h"

static inline bool dir_type(struct stat sb) {
    if ((sb.st_mode & S_IWOTH) == S_IWOTH
        && (sb.st_mode & S_ISVTX) == S_ISVTX);
    else if ((sb.st_mode & S_IWOTH) == S_IWOTH
             && (sb.st_mode & S_IXOTH) == S_IXOTH);
    else
        return true;
    return false;
}

static inline bool file_type(struct stat sb) {
    if ((sb.st_mode & S_IXUSR) == S_IXUSR)
        return true;
    return false;
}

static inline void cf_add_symvol(t_obj *d, const bool *fl) {
    if (d->type < perm_denied && d->type >= fifo) {
        if (d->type == fifo && !fl[p])
            d->s_name[mx_strlen(d->s_name)] = '|';
        else if (d->type == sock && !fl[p])
            d->s_name[mx_strlen(d->s_name)] = '=';
        else if (d->type == lnk && !fl[p])
            d->s_name[mx_strlen(d->s_name)] = '@';
        else if (d->type == dir || d->type == dot_dir) {
            if (dir_type(d->st) || d->type == dot_dir)
                d->s_name[mx_strlen(d->s_name)] = '/';
        }
        else if (d->type == file && !fl[p])
            if(file_type(d->st))
                d->s_name[mx_strlen(d->s_name)] = '*';
    }
}

void cf_flag_F_and_p(t_obj **d, int d_amt, const bool *fl) {
    if (fl[F] || fl[p]) {
        for(int i = 0; i < d_amt; i++)
            cf_add_symvol(d[i], fl);
        for (int i = 0; i < d_amt; i++)
            if (d[i]->kids_amt)
                cf_flag_F_and_p(d[i]->kids, d[i]->kids_amt, fl);
    }
}
