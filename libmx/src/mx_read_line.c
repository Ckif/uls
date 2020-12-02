#include "libmx.h"

static void write_to_str(char **lineptr, char *src, int n, bool p_flag) {
    int l = mx_strlen_safe(*lineptr);
    if (!src)
        return;
    else if (!*lineptr)
        *lineptr = mx_strnew(n);
    else {
        *lineptr = mx_realloc(*lineptr, l * p_flag + n + 1);
    }
    if (!p_flag)
        mx_memcpy(*lineptr, src, n);
    else
        mx_memcpy((*lineptr) + l, src, n);
    (*lineptr)[l * p_flag + n] = '\0';

}
static void del_from_store(t_rlstore **sr, int fd) {
    (*sr)->count--;
    if ((*sr)->count) {
        (*sr)->fds[fd] = (*sr)->fds[(*sr)->count];
        (*sr)->fds = mx_realloc((*sr)->fds, (*sr)->count * sizeof(int));
        (*sr)->lns[fd] = mx_realloc((*sr)->lns[fd], 
                                    mx_strlen_safe((*sr)->lns[(*sr)->count])
                                    + 1);
        mx_strcpy((*sr)->lns[fd], (*sr)->lns[(*sr)->count]);
        free((*sr)->lns[(*sr)->count]);
        (*sr)->lns = mx_realloc((*sr)->lns, (*sr)->count * sizeof(char *));
    }
    else {
        free((*sr)->fds);
        free((*sr)->lns[0]);
        free((*sr)->lns);
        free(*sr);
        *sr = NULL;
    }
}
static int parse_store(t_rlstore **sr, char **lineptr, char delim, int fd) {
    if(*sr != NULL)
        for ( int i = 0; i < (*sr)->count; i++)
            if (fd == (*sr)->fds[i]) {
                int j;
                for (j = 0; (*sr)->lns[i][j] && (*sr)->lns[i][j] != delim; j++);
                write_to_str(lineptr, (*sr)->lns[i], j, false);
                if ((*sr)->lns[i][j] == delim) {
                    mx_memmove((*sr)->lns[i], (*sr)->lns[i] + j + 1, 
                                mx_strlen((*sr)->lns[i] + j) + 1);
                    (*sr)->lns[i] = mx_realloc((*sr)->lns[i],
                                mx_strlen((*sr)->lns[i] + j) + 1);
                    return 2;
                }
                del_from_store(sr, i);
                return 1;
            }
    return 0;
}
static void save_to_store(t_rlstore **sr, int bfs, char *src, int pos, int fd) {
    if (pos + 1 < bfs) {
        int i;

        if (!*sr) {
            *sr = (t_rlstore *)malloc(sizeof(t_rlstore));
            (*sr)->fds = NULL;
            (*sr)->lns = NULL;
            (*sr)->count = 0;
        }
        for (i = 0; i < (*sr)->count; i++);
        (*sr)->lns = mx_realloc((*sr)->lns, (i + 1) * sizeof(char *));
        (*sr)->fds = mx_realloc((*sr)->fds, (i + 1) * sizeof(int));
        (*sr)->lns[i] = (char *)malloc((bfs - pos + 1) * sizeof(char));
        (*sr)->lns[i][bfs - pos] = '\0';
        (*sr)->fds[i] = fd;
        (*sr)->count++;
        mx_memcpy((*sr)->lns[i], src + pos + 1, bfs - pos + 1);
    }
}
static bool parse_buff(char *buff, int buf_size, int *rd, char delim) {
     if (*rd < buf_size)
         buff[*rd] = '\0';
    for (int i = 0; i < *(rd); i++)
        if (buff[i] == delim) {
            *(rd) = i;
            return true;
        }
    return false;
}
int mx_read_line(char **lineptr, size_t buf_size, char delim, int fd) {
    static t_rlstore *store;
    int rd = buf_size;
    char buff[buf_size + 1];
    bool d_flag = false;
    int p_flag;

    if (!buf_size || read(fd, NULL, 0) < 0 || fd == -2)
        return -2;;
    buff[buf_size] = '\0';
    p_flag = parse_store(&store, lineptr, delim, fd);
    if (p_flag == 2)
        return mx_strlen(*lineptr);
    while (rd == (int)buf_size && !d_flag) {
        rd = read(fd, buff, buf_size);
        if (!rd)
            break;
        d_flag = parse_buff(buff, (int)buf_size, &rd, delim);
        write_to_str(lineptr, buff, rd, p_flag);
        p_flag = 1 * (rd != 0);
    }
    if (d_flag)
        save_to_store(&store, (int)buf_size, buff, rd, fd);
    if (!rd && !p_flag && !d_flag)
        return -1;
    return mx_strlen(*lineptr);
}
