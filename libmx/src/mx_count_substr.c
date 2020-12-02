#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int count = 0;
    int sub_len = mx_strlen_safe(sub);

    if (!str || !sub)
        return -1;
    else if (mx_strlen(sub) == 0 || mx_strlen(str) == 0)
        return 0;
    while (sub_len <= mx_strlen(str)) {
        if (mx_strstr(str, sub)) {
            str = mx_strstr(str, sub);
            str += sub_len;
            count++;
        }
        else
            return count;
    }
    return count;
}
