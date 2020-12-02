#include "uls.h"

t_lout wc_getSizesForL(t_obj **fp, int fp_amt, bool *fl) {
    t_lout r;
    struct passwd* tmp = getpwuid(fp[0]->st.st_uid);
    struct group *tmp_g = getgrgid(fp[0]->st.st_gid);
    int link = fp[0]->st.st_nlink;
    r.d_size = 0;
    r.total = 0;
    r.b_owner = 0;
    r.c_group = 0;
    r.d_minor = false;
    for (int i = 0; i < fp_amt; i++) {
        //Column 2 (links)
        if (link < fp[i]->st.st_nlink)
            link = fp[i]->st.st_nlink;
        //Column 3 (owner)
        tmp = getpwuid(fp[i]->st.st_uid);
        if (tmp && !fl[n] && r.b_owner < mx_strlen_safe(tmp->pw_name))
            r.b_owner = mx_strlen_safe(tmp->pw_name);
        else if (!tmp && r.b_owner < wc_getBitDepth(fp[i]->st.st_uid))
            r.b_owner = wc_getBitDepth(fp[i]->st.st_uid);
        //Column 4 (group)
        tmp_g = getgrgid(fp[i]->st.st_gid);
        if (tmp_g && !fl[n] && r.c_group < mx_strlen_safe(tmp_g->gr_name))
            r.c_group = mx_strlen_safe(tmp_g->gr_name);
        else if (!tmp_g && r.c_group < wc_getBitDepth(fp[i]->st.st_gid))
            r.c_group = wc_getBitDepth(fp[i]->st.st_gid);
        // Column 5 (size)
        if (fp[i]->type == chr || fp[i]->type == blk || fp[i]->type == sock) {
            r.d_size = r.d_size < 9 ? 9 : r.d_size;
            r.d_minor = true;
        }
        else if (r.d_size < wc_getBitDepth(fp[i]->st.st_size))
            r.d_size = wc_getBitDepth(fp[i]->st.st_size);
        r.total += fp[i]->st.st_blocks;
    }
    r.a_link = wc_getBitDepth(link);
    return r;
}

