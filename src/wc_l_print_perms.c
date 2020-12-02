#include "uls.h"

static inline void printPerms_firstChar(struct stat st) {
    mx_printchar(S_ISBLK(st.st_mode) ? 'b' :
                    S_ISCHR(st.st_mode) ? 'c' :
                    S_ISDIR(st.st_mode) ? 'd' :
                    S_ISSOCK(st.st_mode) ? 's' :
                    S_ISFIFO(st.st_mode) ? 'p' :
                    S_ISLNK(st.st_mode) ? 'l' : '-');
}/*--------------------------------------------------------------------------*/
static inline void printPerms_lastChar(char *p) {
    mx_printchar(listxattr(p, NULL, 0, XATTR_NOFOLLOW) > 0 ? ('@') :
                    acl_get_file(p, ACL_TYPE_EXTENDED) != NULL ? '+' : ' ');
}/*==========================================================================*/
 void wc_printPerms(struct stat st, char *p) {
    printPerms_firstChar(st);
    //Chars 2 & 3
    mx_printchar((st.st_mode & S_IRUSR) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWUSR) ? 'w' : '-');
    //Char 4
    mx_printchar((st.st_mode & S_IXUSR) ?
                ((st.st_mode & S_ISUID) ? 's' : 'x') :
                ((st.st_mode & S_ISUID) ? 'S' : '-'));
    //Chars 5 & 6
    mx_printchar((st.st_mode& S_IRGRP) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWGRP) ? 'w' : '-');
    //Char 7
    mx_printchar((st.st_mode & S_IXGRP) ?
                ((st.st_mode & S_ISGID) ? 's' : 'x') :
                ((st.st_mode & S_ISGID) ? 'S' : '-'));
    //char 8 & 9
    mx_printchar((st.st_mode& S_IROTH) ? 'r' : '-');
    mx_printchar((st.st_mode & S_IWOTH) ? 'w' : '-');
    //Char 10
    mx_printchar((st.st_mode & S_IXOTH) ?
                ((st.st_mode & S_ISTXT) ? 't' : 'x') :
                ((st.st_mode & S_ISTXT) ? 'T' : '-'));
    printPerms_lastChar(p);
}
