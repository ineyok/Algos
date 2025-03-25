// O(n * log(n))

// Найти c[i] = sum(a[j] * b[k]), j or k == i

// a -> sum_over_subsets(a)
// b -> sum_over_subsets(b)
// c[i] = a[i] * b[i]
// c -> inverse_sum_over_subsets(a)
vector<ll> sos(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> sos = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if((mask >> bit) & 1) sos[mask] += sos[mask - (1 << bit)];
        }
    }
    return sos;
}
vector<ll> inverse_sos(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> sos = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if((mask >> bit) & 1) sos[mask] -= sos[mask - (1 << bit)];
        }
    }
    return sos;
}
vector<ll> or_convolution(vector<ll> a, vector<ll> b) {
    int n = siz(a), k = __lg(siz(a));
    if((1 << k) < n) k++;
    a.resize(1 << k), b.resize(1 << k);
    a = sos(a);
    b = sos(b);
    vector<ll> c(1 << k);
    for(int i = 0; i < (1 << k); ++i) c[i] = a[i] * b[i];
    c = inverse_sos(c);
    c.resize(n);
    return c;
}



// Найти c[i] = sum(a[j] * b[k]), j and k == i

// a -> sum_over_supersets(a)
// b -> sum_over_supersets(b)
// c[i] = a[i] * b[i]
// c -> inverse_sum_over_supersets(a)
vector<ll> sos(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> sos = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if(((mask >> bit) & 1) == 0) sos[mask] += sos[mask + (1 << bit)];
        }
    }
    return sos;
}
vector<ll> inverse_sos(vector<ll> & a) {
    int k = __lg(siz(a));
    vector<ll> sos = a;
    for(int bit = 0; bit < k; ++bit) {
        for(int mask = 0; mask < (1 << k); ++mask) {
            if(((mask >> bit) & 1) == 0) sos[mask] -= sos[mask + (1 << bit)];
        }
    }
    return sos;
}
vector<ll> and_convolution(vector<ll> a, vector<ll> b) {
    int n = siz(a), k = __lg(siz(a));
    if((1 << k) < n) k++;
    a.resize(1 << k), b.resize(1 << k);
    a = sos(a);
    b = sos(b);
    vector<ll> c(1 << k);
    for(int i = 0; i < (1 << k); ++i) c[i] = a[i] * b[i];
    c = inverse_sos(c);
    c.resize(n);
    return c;
}
