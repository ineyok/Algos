// O(log2(n)) на запрос

// Дерево отрезков с отсортированным вектором элементов в вершине
// ? кол-во элементов <x на отрезке [l, r]
// ! изменение в точке, если хранить Treap в вершине

struct Merge_sort_tree {
    int n;
    vector<vector<int>> tree;
    void build(int v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            tree[v] = {ar[vl]};
            return;
        }
        int vm = (vl + vr) / 2;
        build(v * 2 + 1, vl, vm, ar);
        build(v * 2 + 2, vm + 1, vr, ar);
        tree[v].resize(vr - vl + 1);
        merge(all(tree[v * 2 + 1]), all(tree[v * 2 + 2]), tree[v].begin());
    }
    Merge_sort_tree(vector<int> & ar) {
        n = ar.size();
        tree.resize(n * 4);
        build(0, 0, n - 1, ar);
    }

    int query(int v, int vl, int vr, int l, int r, int x) {
        if(r < vl || vr < l) return 0;
        if(l <= vl && vr <= r) {
            return upper_bound(all(tree[v]), x) - tree[v].begin();
        }
        int vm = (vl + vr) / 2;
        return query(v * 2 + 1, vl, vm, l, r, x) + query(v * 2 + 2, vm + 1, vr, l, r, x);
    }
    int query(int l, int r, int x) { return query(0, 0, n - 1, l, r, x); }
};
