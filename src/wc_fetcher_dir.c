#include "uls.h"

static inline bool isDot(char *name) {
    return !mx_strcmp(name, ".") || !mx_strcmp(name, "..");
}/*--------------------------------------------------------------------------*/
static inline bool isHidden(char *name) {
    return name[0] == '.';
}/*--------------------------------------------------------------------------*/
static inline t_obj *initDir(char *p, bool *fl) {
    DIR *dp;
    struct dirent *ep;
    int count = 0;
    t_obj *d = NULL;
    struct stat stats;

    d = (t_obj *)malloc(sizeof(t_obj));
    d->path_name = mx_strjoin(p, " ");
    d->path_name[mx_strlen(d->path_name) - 1] = '\0';
    d->s_name = wc_getShortName(d->path_name);

    dp = opendir (p);
    if (dp == NULL) {
        d->kids_amt = 0;
        d->kids = NULL;
        d->type = perm_denied;
        d->is_root = false;
        d->is_deadl = false;
        fl[err] = true;
    } 
    else {
        while ((ep = readdir(dp)))
            if (!isHidden(ep->d_name) || fl[a] || (fl[A] && !isDot(ep->d_name)))
                count++;
        d->kids = (t_obj **)malloc(sizeof(t_obj *) * count);
        d->kids_amt = count;
        count = fl[L] ? stat(p, &stats) : lstat(p, &stats);
        d->is_deadl = count ? true : false;;
        count = count ? lstat(p, &stats) : count;
        d->type = wc_getType(stats);
        d->is_root = false;
        closedir(dp);
    }
    return d;
}/*--------------------------------------------------------------------------*/
static inline char *addPrefix(char *prefix, char *str) {
    char *t1 = NULL;
    char *t2 = NULL;

    if (prefix[mx_strlen_safe(prefix) - 1] != '/') {
        t1 = mx_strjoin(prefix, "/");
        t2 = mx_strjoin(t1, str);
        free(t1);
        t1 = mx_strjoin(t2, " ");
        t1[mx_strlen(t1) - 1] = '\0';
        free(t2);
    } else {
        t2 = mx_strjoin(prefix, str);
        t1 = mx_strjoin(t2, " ");
        t1[mx_strlen(t1) - 1] = '\0';
        free(t2);
    }
    return t1;
}/*==========================================================================*/
t_obj *wc_fetchDirInfo(char *p, bool *fl) {
    DIR *dp;
    char *buf = NULL;
    struct dirent *ep;
    t_obj *res = initDir(p, fl);
    int e;

    dp = opendir (p);
    if (dp) {
        for (int i = 0; (ep = readdir(dp));)
            if (!isHidden(ep->d_name) || fl[a] || (fl[A] && !isDot(ep->d_name))) {
                if (fl[R] && ep->d_type == DT_DIR && !isDot(ep->d_name)) {
                    buf = addPrefix(p, ep->d_name);
                    res->kids[i] = wc_fetchDirInfo(buf, fl);
                    free(buf);
                } else {
                    res->kids[i] = (t_obj *)malloc(sizeof(t_obj));
                    res->kids[i]->path_name = addPrefix(p, ep->d_name);
                    res->kids[i]->s_name = wc_getShortName(res->kids[i]->path_name);
                    res->kids[i]->kids_amt = 0;
                    res->kids[i]->kids = NULL;
                }
                res->kids[i]->is_root = false;

                e = fl[L] ? stat(res->kids[i]->path_name, &(res->kids[i]->st)) :
                            lstat(res->kids[i]->path_name, &(res->kids[i]->st));
                res->kids[i]->is_deadl = e ? true : false;
                e = e ? lstat(res->kids[i]->path_name, &(res->kids[i]->st)) : e;
                if (res->kids[i]->type != perm_denied)
                    res->kids[i]->type = wc_getType(res->kids[i]->st);
                res->kids[i]->type = isDot(ep->d_name) ? dot_dir : res->kids[i]->type;
                i++;
            }
        closedir(dp);
    } else
        fl[err] = true;
    return res;
}
