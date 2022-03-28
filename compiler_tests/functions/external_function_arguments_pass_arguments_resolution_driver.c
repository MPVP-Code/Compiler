
int g(int a, int b) {
    return a - b;
}

int f(int a, int b);

int main()
{
    return !(f(10, 50)==60);
}
