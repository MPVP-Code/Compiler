int f(int outer, int inner) {
    int result = 0;
    int outerCounter = 1;
    int innerCounter = 1;
    while (outerCounter <= outer) {
        while (innerCounter <= inner) {
            result = result + 1;
            innerCounter = innerCounter + 1;
        }
        outerCounter = outerCounter + 1;
        innerCounter = 1;
    }
    return result;
}