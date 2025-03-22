using mint = uint64_t;

// Строки

mint P = 1718191, degp[mxN], h[mxN];
mint get_hash(int l, int r) {
    mint x = h[r];
    if(l) x -= h[l - 1] * degp[r - l + 1];
    return x;
}
// main()
string s;
h[0] = s[0];
degp[0] = 1;
for(int i = 1; i < siz(s); ++i) {
    h[i] = h[i - 1] * P + s[i];
    degp[i] = degp[i - 1] * P;
}


// Мультимножества

binpow(mint a, int n) {
    ...
}
mint P = 1718191;
// main()
mint h = 0;
h +-= binpow(P, x); // add(x) / erase(x)


// Корневое дерево - как мультимножество хешей детей (в листьх INF)
