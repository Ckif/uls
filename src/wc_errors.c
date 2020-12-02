#include "uls.h"
  void wc_errorNoPath(char *path) {
    mx_printerr("uls: ");
    mx_printerr(path);
    mx_printerr(": No such file or directory\n");
}/*--------------------------------------------------------------------------*/
void wc_errorPermDenied(char *name_of_dir) {
    for (int i = mx_strlen(name_of_dir); i >= 0; i--) {
        if (name_of_dir[i] == '/') {
            name_of_dir += i + 1;
            break;
        }
    }
    errno = 1;
    mx_printerr("uls: ");
    mx_printerr(name_of_dir);
    mx_printerr(": Permission denied\n");
}
