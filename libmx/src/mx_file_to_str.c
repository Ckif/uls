#include "libmx.h"

static int mx_filename_validity(const char *filename) {
    int src = open(filename, O_RDONLY | O_DIRECTORY);

    if (src < 0) {
        src = open(filename, O_RDONLY);
        if (src > 0) {
            if (read(src, NULL, 1)) {
                close(src);
                return 1;
            }
            close(src);
            return 0;
        }
        return -1;
    }
    return -2;
}
char *mx_file_to_str(const char *filename) {
    if (mx_filename_validity(filename)) {
        int src = open(filename, O_RDONLY);
        int count;
        char buff[64];
        char *text = NULL;
        int rd = read(src, &buff, sizeof(buff));

        for (count = rd; rd == 64; count += rd)
            rd = read(src, buff, sizeof(buff));

        text = (char *)malloc(sizeof(char) * count + 1);
        src = open(filename, O_RDONLY); 
        rd = read(src, text, count);
        text[count] = '\0';
        return text;
    }
    return NULL;
}
