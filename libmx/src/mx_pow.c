double mx_pow(double n, unsigned int pow) {
    double original = n;

    if (!pow)
        return 1;
    while (--pow)
        n *= original;
    return n;
}
