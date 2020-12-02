#include "uls.h"

t_obj *wc_fetchFileInfo(char *p, bool *fl) {
    t_obj *f = (t_obj *)malloc(sizeof(t_obj));
    int e = fl[L] ? stat(p, &(f->st)) : lstat(p, &(f->st));
    
    f->is_deadl = e ? true : false;
    e = e ? lstat(p, &(f->st)) : e;
    f->path_name = mx_strjoin(p, " ");
    f->path_name[mx_strlen(f->path_name) - 1] = '\0';
    f->s_name = wc_getShortName(p);
    f->kids_amt = 0;
    f->kids = NULL;
    f->type = wc_getType(f->st);
    f->is_root = false;
    return f;
}
