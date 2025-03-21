// написано на отрезках
// запрос максимум на отрезке
// изменение прибавление на отрезке

struct Segtree {
    int n;
    vector<ll> tree, lazy;
    void build(int v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            tree[v] = ar[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(v * 2 + 1, vl, vm, ar);
        build(v * 2 + 2, vm + 1, vr, ar);
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
    Segtree(vector<int> & ar) {
        n = size(ar);
        tree.resize(n * 4);
        lazy.resize(n * 4);
        build(0, 0, n - 1, ar);
    }

    void push(int v, int vl, int vr) {
        if(!lazy[v]) return;
        tree[v] += lazy[v];
        if(vl != vr) {
            lazy[v * 2 + 1] += lazy[v];
            lazy[v * 2 + 2] += lazy[v];
        }
        lazy[v] = 0;
    }

    ll query(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if(r < vl || vr < l) return -INF;
        if(l <= vl && vr <= r) return tree[v];
        int vm = (vl + vr) / 2;
        return max(query(v * 2 + 1, vl, vm, l, r), query(v * 2 + 2, vm + 1, vr, l, r));
    }
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }

    void update(int v, int vl, int vr, int l, int r, int x) {
        push(v, vl, vr);
        if(r < vl || vr < l) return;
        if(l <= vl && vr <= r) {
            lazy[v] = x;
            push(v, vl, vr);
            return;
        }
        int vm = (vl + vr) / 2;
        update(v * 2 + 1, vl, vm, l, r, x);
        update(v * 2 + 2, vm + 1, vr, l, r, x);
        tree[v] = tree[v * 2 + 1] + tree[v * 2 + 2];
    }
    void update(int l, int r, int x) { update(0, 0, n - 1, l, r, x); }
};
