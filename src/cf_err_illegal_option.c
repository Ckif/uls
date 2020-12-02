#include"uls.h"

void cf_err_illegal_option(char *flags_char) {
    for (int i = 0; flags_char[i]; i++) {
        if (mx_strchr(FLAG_LIST, flags_char[i]) == 0) {
            mx_printerr("uls: illegal option -- ");
            mx_printerr(&flags_char[i]);
            mx_printerr("\n");
            mx_printerr("usage: uls [-");
            mx_printerr(FLAG_LIST);
            mx_printerr("] [file ...]\n");
            exit(1);
        }
    }
}
