int f(int n) {
    for (int i = 0; i < 10; i++) {
        n++;
        if (i > 5) {
            break;
        }
    }
    return n;
}