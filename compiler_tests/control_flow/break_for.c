int f(int n) {
    int b = 0;
    int i = 0;
    for (i = 0; i < n; i++) {
        if (i > 3) {
            break;
        }
        b++;
    }
    return b;
}