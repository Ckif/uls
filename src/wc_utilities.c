#include "uls.h"

short wc_getBitDepth(int a) {
    short r = 0;

    a = (a == 0) ? 1 : a;
    while (a) {
        a = a / 10;
        r++;
    }
    return r;
}/*--------------------------------------------------------------------------*/
char *wc_getShortName(char *p) {
    int l = mx_strlen_safe(p) - 1;

    for (;l > 0 && p[l] != '/'; l--);
    l += (p[l] == '/');
    p += l;
    return p;
}//*--------------------------------------------------------------------------*/
char wc_getType(struct stat st) {
    return S_ISFIFO(st.st_mode) ? fifo :
            S_ISBLK(st.st_mode) ? blk : 
            S_ISCHR(st.st_mode) ? chr :
            S_ISSOCK(st.st_mode) ? sock :
            S_ISLNK(st.st_mode) ? lnk : 
            S_ISDIR(st.st_mode) ? dir : file;
}/*--------------------------------------------------------------------------*/// void *wc_printDouble(double *) {
void wc_printDouble(double n) {
    int temp = (n - (int)n) * 100;
    int i = mx_pow(10, wc_getBitDepth((int)n));
    n += temp % 10 > 4 ? .1 : 0;
    n += i > 10 && temp % 100 > 50 ? 1 : 0;
    mx_printstr(i == 100 ? " " : "");
    mx_printint((int)n % i);
    if (i < 100) {
        mx_printchar('.');
        mx_printint((int)((n - (int)n) * 10));
    }
}//*--------------------------------------------------------------------------*/

