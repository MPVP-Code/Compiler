int f(int n) {
    int b = 0;
    do {
        n++;
        if (n > 5) {
            continue;
        }
        b++;
    } while (n < 10);
    return b;
}