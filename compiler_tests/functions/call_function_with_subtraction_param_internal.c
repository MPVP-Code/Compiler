int g(int n) {
    return 10 + n;
}

int f(int n)
{
    if(n==0){
        return 0;
    }
    return n+g(n-1);
}
