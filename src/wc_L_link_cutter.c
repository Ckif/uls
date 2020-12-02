#include "uls.h"


void wc_cutDeadLinks(t_obj **dir, int dir_amt, bool *fl) {
    if (fl[L] && (fl[G] || fl[l] || fl[p] || fl[F] || fl[R] || fl[t] || fl[S])) {
        for (int i = 0; i < dir_amt; i++)
            for (int j = 0; j < dir[i]->kids_amt; j++)
                if (dir[i]->kids[j]->is_deadl) {
                    dir[i]->kids_amt--;
                    wc_freeObj(dir[i]->kids[j]);
                    dir[i]->kids[j] = dir[i]->kids[dir[i]->kids_amt];
                    dir[i]->kids[dir[i]->kids_amt] = NULL;
                }
    }
}
