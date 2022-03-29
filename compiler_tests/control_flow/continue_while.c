int f(int n) {
    int b = 0;
    while (n < 10) {
        n++;
        if (n > 5) {
            continue;
        }
        b++;
    }
    return b;
}