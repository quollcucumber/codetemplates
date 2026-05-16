const int MOD = 1e9 + 7;
int power(int a, int b) {
    if (b == 0) return 1;
    int x = power(a * a % MOD, b / 2);
    return b % 2 ? x * a % MOD : x;
}
int inv(int a) {
    return power(a, MOD - 2);
}
