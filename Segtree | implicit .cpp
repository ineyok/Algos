// Неявное дерево отрезков
// ? Сумма на отрезке
// ! Прибавление на отрезке

struct Segtree {
    struct Node {
        ll sum, lazy_add;
        int l, r;
        Node() : sum(0), lazy_add(0), l(-1), r(-1) {}
    };
    void init_ch(int v) {
        if(tree[v].l == -1) {
            tree[v].l = size(tree);
            tree.push_back(Node());
        }
        if(tree[v].r == -1) {
            tree[v].r = size(tree);
            tree.push_back(Node());
        }
    }

    int C = 1e9 + 7;
    vector<Node> tree;
    int root;
    Segtree() {
        root = 0;
        tree.push_back(Node());
    }

    void push(int v, int vl, int vr) {
        if(!tree[v].lazy_add) return;
        tree[v].sum += tree[v].lazy_add * (vr - vl + 1);
        if(vl != vr) {
            init_ch(v);
            tree[tree[v].l].lazy_add += tree[v].lazy_add;
            tree[tree[v].r].lazy_add += tree[v].lazy_add;
        }
        tree[v].lazy_add = 0;
    }

    ll query(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if(r < vl || vr < l) return 0;
        if(l <= vl && vr <= r) return tree[v].sum;
        init_ch(v);
        int vm = (vl + vr) / 2;
        return query(tree[v].l, vl, vm, l, r) + query(tree[v].r, vm + 1, vr, l, r);
    }
    ll query(int l, int r) { return query(root, 0, C - 1, l, r); }

    void update(int v, int vl, int vr, int l, int r, ll x) {
        push(v, vl, vr);
        if(r < vl || vr < l) return;
        if(l <= vl && vr <= r) {
            tree[v].lazy_add = x;
            push(v, vl, vr);
            return;
        }
        init_ch(v);
        int vm = (vl + vr) / 2;
        update(tree[v].l, vl, vm, l, r, x);
        update(tree[v].r, vm + 1, vr, l, r, x);
        tree[v].sum = tree[tree[v].l].sum + tree[tree[v].r].sum;
    }
    void update(int l, int r, ll x) { update(root, 0, C - 1, l, r, x); }
};
