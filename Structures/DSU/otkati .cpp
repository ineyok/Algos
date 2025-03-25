// O(log(n)) на запрос

// DSU с откатами

struct DSU_o {
    vector<int> pr, sz, vers;
    vector<vector<int>> mem;

    DSU_o()=default;
    DSU_o(int n) : pr(n), sz(n, 1) {
        iota(all(pr), 0);
    }

    int root(int v) { return (pr[v] == v ? v : root(pr[v])); }
    bool connect(int a, int b) { return root(a) == root(b); }

    void merge(int a, int b) {
        a = root(a), b = root(b);
        if(a == b) return;
        if(sz[a] < sz[b]) swap(a, b); // a <- b
        mem.push_back({a, sz[a], b, pr[b]});
        sz[a] += sz[b];
        pr[b] = a;
    }

    void add_vers() { vers.push_back(siz(mem)); }
    void del_vers() {
        while(siz(mem) > vers.back()) {
            sz[mem.back()[0]] = mem.back()[1];
            pr[mem.back()[2]] = mem.back()[3];
            mem.pop_back();
        }
        vers.pop_back();
    }
};
