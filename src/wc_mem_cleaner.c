#include "uls.h"

void wc_freePath(t_path *p) {
    if(p == NULL)
        return;

    free(p->isdir);
    for (int i = 0; i < p->amt; i++)
        free(p->path[i]);
    free(p->path);
    free(p);
}/*--------------------------------------------------------------------------*/
void wc_freeObj(t_obj *o) {
    if(o == NULL)
        return;
    free(o->path_name);
    for (int i = 0; i < o->kids_amt; i++)
        wc_freeObj(o->kids[i]);
    if(o->kids_amt)
        free(o->kids);
    free(o);
}/*--------------------------------------------------------------------------*/
void wc_freeData(t_data *d) {
    if(d == NULL)
        return;

    for (int i = 0; i < d->files_amt; i++)
        wc_freeObj(d->files_path[i]);
    for (int i = 0; i < d->dirs_amt; i++)
        wc_freeObj(d->dirs_path[i]);
    free(d->files_path);
    free(d->dirs_path);
    free(d);
}

