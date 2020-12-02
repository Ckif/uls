#include "uls.h"

static inline bool usePathName(char *p) {
    while (*p) {
        if (p[0] == '/' && p[1] != '\0')
            return true;
        p++;
    }
    return false;
}
t_data *wc_fetchData(t_path *p, bool *fl) {
    int dcount = 0;
    t_data *res = NULL;

    if (p) {
        for (int i = 0; i < p->amt; i++)
            dcount += p->isdir[i];
        res = (t_data *)malloc(sizeof(t_data));

        res->dirs_amt = dcount;
        res->files_amt = p->amt - dcount;
        res->dirs_path = NULL;
        res->files_path = NULL;
        if (res->dirs_amt)
            res->dirs_path = (t_obj **)malloc(sizeof(t_obj *) * res->dirs_amt);
        if (res->files_amt)
            res->files_path = (t_obj **)malloc(sizeof(t_obj *) * res->files_amt);
        
        for (int i = 0, j = 0, k = 0; k < p->amt; k++) {
            if (p->isdir[k]) {
                res->dirs_path[j++] = wc_fetchDirInfo(p->path[k], fl);
                if (usePathName(p->path[k])) {
                    res->dirs_path[j - 1]->s_name = res->dirs_path[j - 1]->path_name;
                    res->dirs_path[j - 1]->is_root = true;
                }
            }
            else {
                res->files_path[i++] = wc_fetchFileInfo(p->path[k], fl);
                if (usePathName(p->path[k])) {
                    res->files_path[i - 1]->s_name = res->files_path[i - 1]->path_name;
                    res->files_path[i - 1]->is_root = true;
                }
            }
        }
    }
    return res;
}
