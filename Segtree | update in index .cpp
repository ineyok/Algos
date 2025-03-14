// написано на отрезках
// запрос максимума от отрезке
// присвоение в точке


struct Segtree {
    int n;
    vector<int> tree;
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
        build(0, 0, n - 1, ar);
    }

    int query(int v, int vl, int vr, int l, int r) {
        if(r < vl || vr < l) return -INF;
        if(l <= vl && vr <= r) return tree[v];
        int vm = (vl + vr) / 2;
        return max(query(v * 2 + 1, vl, vm, l, r), query(v * 2 + 2, vm + 1, vr, l, r));
    }
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }

    void update(int v, int vl, int vr, int i, int x) {
        if(vl == vr) {
            tree[v] = x;
            return;
        }
        int vm = (vl + vr) / 2;
        if(i <= vm) update(v * 2 + 1, vl, vm, i, x);
        else update(v * 2 + 2, vm + 1, vr, i, x);
        tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
    void update(int i, int x) { update(0, 0, n - 1, i, x); }
};
