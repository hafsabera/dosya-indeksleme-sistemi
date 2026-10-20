#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int lcm_recursive(int a, int b, int x) {
    if (x % a == 0 && x % b == 0)
        return x;
    return lcm_recursive(a, b, x + 1);
}

int lcm(int a, int b) {
    if (a > b)
        return lcm_recursive(a, b, a);
    else
        return lcm_recursive(a, b, b);
}

int main() {
    int secim, a, b;

    printf("1. En Buyuk Ortak Boleni Hesapla\n");
    printf("2. En Kucuk Ortak Kati Hesapla\n");

    scanf("%d", &secim);
    scanf("%d %d", &a, &b);

    if (secim == 1) {
        printf("EBOB = %d", gcd(a, b));
    }
    else if (secim == 2) {
        printf("EKOK = %d", lcm(a, b));
    }

    return 0;
}

