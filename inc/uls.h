#pragma once

#include "libmx.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <time.h>

#define FLAG_LIST "ACFGHLRSTUacdefghlmnoprtu1@"
#define INT_MAX 2147483647
#define PATH_MAX 1024
#define BIBYTE 1024

#define RED       "\x1B[31m"
#define GRN       "\x1B[32m"
#define YEL       "\x1B[33m"
#define BLU       "\x1B[1m\x1B[36m"
#define MAG       "\x1B[35m"
#define RESET     "\x1B[0m"
#define BLK_F_RED_B "\x1B[0;30;41m"
#define BLK_F_CYAN_B "\x1B[0;30;46m"
#define BLOCK "\x1B[0;34;46m"
#define CHR "\x1B[0;34;43m"
#define DIR_T "\x1B[0;30;42m"
#define DIR_X "\033[0;30;43m"

//----------------------------------Enums------------------------------------//
enum flags {
    G,
    U,
    F,
    f,
    a,
    A,
    R,
    l,
    one,
    m,
    C,
    S,
    t,
    r,
    p,
    u,
    c,
    dog,
    e,
    h,
    T,
    d,
    L,
    H,
    n,
    o,
    g,
    tty,
    err,
    ALL_FLAGS,
};
enum types {
    fifo,
    chr,
    blk,
    lnk,
    sock,
    dir,
    file,
    dot_dir,
    perm_denied,
};
//----------------------------------Structs----------------------------------//
typedef struct s_path {
    char **path;
    bool *isdir;
    int amt;
}              t_path;
typedef struct s_obj {
    struct s_obj **kids;
    char *path_name;
    char *s_name;
    struct stat st;
    int kids_amt;
    char type;
    bool is_root;
    bool is_deadl;
}              t_obj;
typedef struct s_data {
    t_obj **dirs_path;
    t_obj **files_path;
    int dirs_amt;
    int files_amt;
}               t_data;
typedef struct s_lout {
    int total;
    short a_link;
    short b_owner;
    short c_group;
    short d_size;
    bool d_minor;
}               t_lout;

//----------------------------------Fetchers---------------------------------//
t_path *wc_getPaths(int argc, char *argv[], bool *fl);
t_obj *wc_fetchDirInfo(char *p, bool *fl);
t_obj *wc_fetchFileInfo(char *p, bool *fl);
//----------------------------------Managers---------------------------------//
t_data *wc_fetchData(t_path *p, bool *fl);
void wc_printResult(t_data *d, bool *flocktimeout);
//----------------------------------Printers---------------------------------//
void wc_printName(t_obj *obj, bool *fl);
void wc_printWithC(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithOne(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithM(t_obj **fp, int fp_amt, bool *fl);
void wc_printWithL(t_obj **fp, int fp_amt, bool *fl, bool use_total);
t_lout wc_getSizesForL(t_obj **fp, int fp_amt, bool *fl);
void wc_printPerms(struct stat st, char *p);
void wc_printStats(struct stat st, t_lout l, bool *fl);
void wc_printTime(struct stat st, bool *fl);
//----------------------------------Sorter-----------------------------------//
void wc_quicksortObj(t_obj **arr, int l, int r, bool cmp(t_obj *, t_obj *));
//----------------------------------Utilities---------------------------------//
char *wc_getShortName(char *p);
short wc_getBitDepth(int a);
char wc_getType(struct stat st);
void wc_printDouble(double n);
//----------------------------------Cleaners---------------------------------//
void wc_cutDeadLinks(t_obj **dir, int dir_amt, bool *fl);
void wc_freePath(t_path *p);
void wc_freeObj(t_obj *o);
void wc_freeData(t_data *d);
//----------------------------------Errors-----------------------------------//
void wc_errorNoPath(char *path);
void wc_errorPermDenied(char *name_of_dir);
void wc_printTime(struct stat st, bool *fl);
/*----------------------------------Ckif-------------------------------------*/
bool *cf_flags_num (int argc, char *argv[]);
bool *cf_cmp_flags(bool *fls);
void cf_err_illegal_option(char *flags_char);
bool *cf_isatty(bool *fls);
bool *cf_bool_manip(int argc, char **argv);
void cf_flags_check (t_data *d, bool *fl);
void cf_flag_r(t_obj **d, int d_amt, const bool *fl);
void cf_flag_S(t_obj **d, int d_amt, const bool *fl);
void cf_flag_t(t_obj **d, int d_amt, const bool *fl);
void cf_flag_u(t_obj **d, int d_amt, const bool *fl);
void cf_flag_c(t_obj **d, int d_amt, const bool *fl);
void cf_flag_Uu(t_obj **d, int d_amt, const bool *fl);
void cf_not_flag_f(t_obj **d, int d_amt, const bool *fl);
void cf_flag_F_and_p(t_obj **d, int d_amt, const bool *fl);
