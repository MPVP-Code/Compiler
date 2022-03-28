int f(int a) {
    int b = --a;
    if (b == a) {
        return 11;
    } else {
        return 10;
    }
}