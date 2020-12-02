#include "uls.h"

static inline void fill_bool(char *flags_char, bool *flags, int count_flags) {
    char flag[ALL_FLAGS] = {'G', 'U', 'F', 'f', 'a', 'A', 'R', 'l', '1',
                            'm', 'C', 'S', 't','r', 'p', 'u', 'c', '@', 'e',
                            'h', 'T', 'd', 'L', 'H','n', 'o', 'g'};

    for (int i = 0; i < ALL_FLAGS; i++)//обнулить буловый массив
        flags[i] = false;
    for (int i = count_flags - 1 ; i >= 0; i--)//убрать дубликаты в строке флагов
        for (int j = i - 1; j >= 0; j--)
            if (flags_char[i] == flags_char[j] && flags_char[i] != '-')
                flags_char[j] = '-';
    for (int i = 0, j = 0; i < count_flags; i++) //дать прaвдивое значение флага в буловом массиве
        for (j = 0; j < ALL_FLAGS; j++)
            if (flags_char[i] == flag[j])
                flags[j] = true;
}

static void char_cmp(int i, int j, char *flags_char, bool *flags) {
    flags_char[j] = '-';
    flags[i] = false;
}

static inline void cmp_flags(char *flags_char, bool *flags, int i, int k) {
    for (int j = i; j >= 0; j--) {
        if (flags_char[j] == 'l')
            char_cmp(l, j, flags_char, flags);
        else if (flags_char[j] == 'm')
            char_cmp(m, j, flags_char, flags);
        else if (flags_char[j] == 'C')
            char_cmp(C, j, flags_char, flags);
        else if (flags_char[j] == '1')
            char_cmp(one, j, flags_char, flags);
        else if (k == 1) {
            if (flags_char[j] == 'o')
                char_cmp(o, j, flags_char, flags);
            else if (flags_char[j] == 'n')
                char_cmp(n, j, flags_char, flags);
            else if (flags_char[j] == 'g')
                char_cmp(g, j, flags_char, flags);
        }
    }
}

static inline void check_perm(char *flags_char, bool *flags, int count_flags) {
    for (int i = count_flags - 1; i >= 0; i--) {
        if (flags_char[i] == 'm' || flags_char[i] == 'C')
            for (int j = i - 1; j >= 0; j--) {
                if (flags_char[j] == 'l' || flags_char[j] == '1')
                    cmp_flags(flags_char, flags, j, 0);
                if (flags_char[j] == 'C' || flags_char[j] == 'm') {
                    cmp_flags(flags_char, flags, j, 0);
                    flags[m] = true;
                }
            }
        else if(flags_char[i] == 'l' || flags_char[i] == 'm' ||
                flags_char[i] == 'C' || flags_char[i] == '1')
            cmp_flags(flags_char, flags, i - 1, 1);
        else if(flags_char[i] == 'o' || flags_char[i] == 'n' ||
                flags_char[i] == 'g')
            cmp_flags(flags_char, flags, i - 1, 0);
        else if(flags_char[i] == 'u' || flags_char[i] == 'c')
            for (int j = i - 1; j >= 0; j--) {
                if (flags_char[j] == 'u') {
                    char_cmp(u, j, flags_char, flags);
                }
                else if (flags_char[j] == 'c')
                    char_cmp(c, j, flags_char, flags);
            }

        else if(flags_char[i] == 'F' || flags_char[i] == 'p') {
            for (int j = i - 1; j >= 0; j--) {
                if (flags_char[j] == 'F') {
                    char_cmp(F, j, flags_char, flags);
                } else if (flags_char[j] == 'p')
                    char_cmp(p, j, flags_char, flags);
            }
        }

        else if(flags_char[i] == 'L' || flags_char[i] == 'H') {
            for (int j = i - 1; j >= 0; j--) {
                if (flags_char[j] == 'H') {
                    char_cmp(H, j, flags_char, flags);
                } else if (flags_char[j] == 'L')
                    char_cmp(L, j, flags_char, flags);
            }
        }
    }
}

bool *cf_flags_num (int argc, char *argv[]) {
    int count = 0;
    int count_flags = 0;
    bool *flags = NULL;
    char *flags_char;


    for (int i = 1; i < argc && argv[i][0] == '-' && argv[i][1] != '-'; i++, count++)
        count_flags += mx_strlen(argv[i]) - 1;
    flags_char = mx_strnew(count_flags);
    flags = (bool *)malloc(sizeof(bool) * ALL_FLAGS);
    for (int i = 1, j = 0; i <= count; i++)
        for (int k = 1; argv[i][k] != '\0'; k++, j++)
            flags_char[j] = argv[i][k];
    cf_err_illegal_option(flags_char);
    fill_bool(flags_char, flags, count_flags);
    check_perm(flags_char, flags, count_flags);
//    mx_printstr(flags_char);
//    mx_printstr("\n");
    free(flags_char);
    return flags;
}
