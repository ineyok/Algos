// O(1) на запрос

struct DSU {
    vector<int> pr, sz;

    DSU()=default;
    DSU(int n) : pr(n), sz(n, 1) {
        iota(all(pr), 0);
    }

    int root(int v) { return pr[v] = (pr[v] == v ? v : root(pr[v])); }
    bool connect(int a, int b) { return root(a) == root(b); }

    void merge(int a, int b) {
        a = root(a), b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b];
        pr[b] = a;
    }
};
