unsigned long mx_hex_to_nbr(const char *hex) {
    unsigned long result = 0;
    unsigned long depth = 1;

    if (!hex)
        return 0;
    for (int i = 0; hex[i + 1]; i++)
        depth *= 16;
    for (int i = 0; hex[i]; i++) {
        result += depth * (hex[i] 
                            - 48 * (hex[i] >= 48 && hex[i] <= 57)
                            - 55 * (hex[i] >= 65 && hex[i] <= 70)
                            - 87 * (hex[i] >= 97 && hex[i] <= 102)
                            );
        depth /= 16;
    }
    return result;
}
