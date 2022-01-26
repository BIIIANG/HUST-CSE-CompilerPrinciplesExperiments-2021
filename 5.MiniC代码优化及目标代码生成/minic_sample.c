int calc(int k, int t) {
    return k * t;
}
int main() {
    int a, b;
    int i;
    int target = 1;
    a = getchar();
    a -= 48;
    b = getchar();
    b -= 48;
    i = 0;
    while (i < b) {
        i = i + 1;
        target = target * a;
    }
    putchar(target + 48);
    return 0;
}