int mx_strncmp(const char *s1, const char *s2, int n) {
    int count = 0;

    while (s1[count] == s2[count]) {
        if (s1[count] == '\0' || count+1 == n)
            return 0;
        count++;
    }  
    return s1[count]-s2[count];
}
