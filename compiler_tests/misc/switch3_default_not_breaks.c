int g(int t)
{
    int x;
    x=0;
    switch(t)
    {
        case 0:
            x=1;
        case 2:
            x=2;
            x=10;
        case 1:
            x=x+1;
        default:
            x=t+1;
    }
    return x;
}
