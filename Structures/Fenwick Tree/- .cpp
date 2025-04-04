// O(log(n)) на запрос

// ? сумма на отрезке
// ! прибавление в точке

struct Fenwick {
    int n;
    vector<ll> tree;
    Fenwick(int n_) {
        n = n_;
        tree.resize(n);
    }
    Fenwick(vector<int> & ar) {
        n = size(ar);
        tree.resize(n);
        for(int i = 0; i < n; ++i)
            add(i, ar[i]);
    }

    ll query_sum(int i) {
        ll ans = 0;
        for(; i >= 0; i = (i & (i + 1)) - 1)
            ans += tree[i];
        return ans;
    }
    ll query_sum(int l, int r) { 
        ll ans = query_sum(r);
        if(l) ans -= query_sum(l - 1);
        return ans;
    }

    void add(int i, int x) {
        for(; i < n; i |= i + 1)
            tree[i] += x;
    }
};
