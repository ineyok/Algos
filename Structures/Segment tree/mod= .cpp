// ? Сумма на отрезке
// ! mod= на отрезке
// ! изменение в точке

struct Segtree_Beats {
    int n;
    vector<int> mx;
    vector<ll> sm;
    void build(int v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            mx[v] = sm[v] = ar[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(v * 2 + 1, vl, vm, ar);
        build(v * 2 + 2, vm + 1, vr, ar);
        mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
        sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
    }
    Segtree_Beats(vector<int> & ar) {
        n = size(ar);
        mx.resize(n * 4);
        sm.resize(n * 4);
        build(0, 0, n - 1, ar);
    }

    ll query(int v, int vl, int vr, int l, int r) {
        if(r < vl || vr < l) return 0;
        if(l <= vl && vr <= r) return sm[v];
        int vm = (vl + vr) / 2;
        return query(v * 2 + 1, vl, vm, l, r) + query(v * 2 + 2, vm + 1, vr, l, r);
    }
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }

    void update_mod(int v, int vl, int vr, int l, int r, int x) {
        if(r < vl || vr < l || mx[v] < x) return;
        if(vl == vr) {
            mx[v] %= x;
            sm[v] = mx[v];
            return;
        }
        int vm = (vl + vr) / 2;
        update_mod(v * 2 + 1, vl, vm, l, r, x);
        update_mod(v * 2 + 2, vm + 1, vr, l, r, x);
        mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
        sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
    }
    void update_mod(int l, int r, int x) { update_mod(0, 0, n - 1, l, r, x); }

    void assign(int v, int vl, int vr, int i, int x) {
        if(vl == vr) {
            mx[v] = sm[v] = x;
            return;
        }
        int vm = (vl + vr) / 2;
        if(i <= vm) assign(v * 2 + 1, vl, vm, i, x);
        else assign(v * 2 + 2, vm + 1, vr, i, x);
        mx[v] = max(mx[v * 2 + 1], mx[v * 2 + 2]);
        sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
    }
    void assign(int i, int x) { assign(0, 0, n - 1, i, x); }
};
