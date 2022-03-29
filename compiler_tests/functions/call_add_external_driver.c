int g(int a) {
    return a + 1;
}

int f(int a);

int main() {
    return !(f(10) == 32);
}