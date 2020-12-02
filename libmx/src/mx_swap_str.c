void mx_swap_str(char **a, char **b) {
    char *temp = *a;

    *a = *b;
    *b = temp;
}
