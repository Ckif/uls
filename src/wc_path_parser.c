#include "uls.h"

static inline char checkPath(char *path, bool *fl) {
    struct stat stats;
    int e = stat(path, &stats);
    char t = wc_getType(stats);

    if (!e && (!fl[l] || fl[H] || (fl[L]))) {
        if (t == dir)
            return 1;
        return 2;
    }
    else {
        e = lstat(path, &stats);
        t = wc_getType(stats);
        if (!e) {
            if (t == dir)
                return 1;
            return 2;
        }
    }
    return 0;
}/*--------------------------------------------------------------------------*/
static inline t_path *CurDirPath(bool *fl) {
    t_path *p = (t_path *)malloc(sizeof(t_path));

    p->amt = 1;
    p->isdir = (bool *)malloc(sizeof(bool));
    p->isdir[0] = fl[d] ? false : true;
    p->path = (char **)malloc(sizeof(char *));
    p->path[0] = (char *)malloc(sizeof(char) * 2);
    p->path[0][0] = '.';
    p->path[0][1] = '\0';
    return p;
}/*--------------------------------------------------------------------------*/
static inline t_path *initPaths(int argc, char *argv[], char *status,
                                            int flags, int fakes, bool *fl) {
    t_path *p = NULL;

    if (argc - flags - fakes) {
        p = (t_path *)malloc(sizeof(t_path));
        p->amt = argc - flags - fakes;
        p->path = (char **)malloc(sizeof(char *) * p->amt);
        p->isdir = (bool *)malloc(sizeof(bool) * p->amt);
    }
    for (int i = 0, j = 0; j < argc - flags; j++) {
        if (status[j] == 1) {
            p->isdir[i] = true;
            p->path[i++] = mx_strdup(argv[j + flags]);
            if (p->path[i - 1][mx_strlen(p->path[i - 1])] == '/')
                p->path[i - 1][mx_strlen(p->path[i - 1])] = '\0';
        } else if(status[j] == 2) {
            p->isdir[i] = false;
            p->path[i++] = mx_strdup(argv[j + flags]);
        } else {
            wc_errorNoPath(argv[j + flags]);
            fl[err] = true;
        }
    }

    free(status);
    return p;
}/*==========================================================================*/
t_path *wc_getPaths(int argc, char *argv[], bool *fl) {
    int fakes = 0;
    int flags = 1;
    char *status = NULL;

    if (argc > 1)
        while (argv [flags] && argv[flags][0] == '-')
            if (argv[flags++][1] == '-')
                break;

    if (argc - flags == 0)
            return CurDirPath(fl);

    status = (char *)malloc(sizeof(char) * (argc - flags));
    for(int i = flags; i < argc; i++) {
        status[i - flags] = checkPath(argv[i], fl);
        // -d flag check
        status[i - flags] = fl[d] ? 2 : status[i - flags];
        fakes += !status[i - flags];
    }
    return initPaths(argc, argv, status, flags, fakes, fl);
}
