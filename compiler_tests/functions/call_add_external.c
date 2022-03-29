int g(int a);

int f(int a) {
    return g(a) + g(a + 10);
}