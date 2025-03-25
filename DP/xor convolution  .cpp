// O(n * log(n))

// Найти c[i] = sum(a[j] * b[k]), j ^ k == i

// a -> hadamard_transform(a)
// b -> hadamard_transform(b)
// c[i] = a[i] * b[i]
// c -> inverse_hadamard_transform(a)
vector<ll> hadamard_transform(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> dp = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if(((mask >> bit) & 1) == 0) {
                ll v0 = dp[mask], v1 = dp[mask + (1 << bit)];
                dp[mask] = v0 + v1;
                dp[mask + (1 << bit)] = v0 - v1;
            }
        }
    }
    return dp;
}
vector<ll> inverse_hadamard_transform(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> dp = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if(((mask >> bit) & 1) == 0) {
                ll s = dp[mask], r = dp[mask + (1 << bit)];
                dp[mask] = (s + r) / 2;
                dp[mask + (1 << bit)] = (s - r) / 2;
            }
        }
    }
    return dp;
}
vector<ll> xor_convolution(vector<ll> a, vector<ll> b) {
    int n = siz(a), k = __lg(siz(a));
    if((1 << k) < n) k++;
    a.resize(1 << k), b.resize(1 << k);
    a = hadamard_transform(a);
    b = hadamard_transform(b);
    vector<ll> c(1 << k);
    for(int i = 0; i < (1 << k); ++i) c[i] = a[i] * b[i];
    c = inverse_hadamard_transform(c);
    c.resize(n);
    return c;
}
