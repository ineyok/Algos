
// Модулярные вычисления

const int MOD = 1e9 + 7;
int add(int a, int b) { return (a + b < MOD ? a + b : a + b - MOD); }
int sub(int a, int b) { return (a - b >= 0 ? a - b : a - b + MOD); }
int mul(int a, int b) { return 1ll * a * b % MOD; }
int binpow(int a, int n) {
    if(!n) return 1;
    if(n % 2) return 1ll * binpow(a, n - 1) * a % MOD;
    int b = binpow(a, n / 2);
    return 1ll * b * b % MOD;
}
