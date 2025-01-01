// ДО на сумму с изменением в точке
// Персистентность по индексам массива

// ? K порядковая статистика на отреке индексов [L:R]

struct Segtree {
    struct Node {
        int sm, l, r;
        Node() : sm(0), l(-1), r(-1) {}
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
    vector<int> roots;
    Segtree(vector<int> & ar) {
        roots.push_back(0);
        tree.push_back(Node());
        for(int el : ar) {
            roots.push_back(update(roots.back(), 0, C - 1, el, 1));
        }
    }

    int query(int v1, int v2, int vl, int vr, int k) {
        if(vl == vr) return vl;
        init_ch(v1);
        init_ch(v2);
        int vm = (vl + vr) / 2;
        int cntl = tree[tree[v2].l].sm - tree[tree[v1].l].sm;
        if(cntl >= k)
            return query(tree[v1].l, tree[v2].l, vl, vm, k);
        return query(tree[v1].r, tree[v2].r, vm + 1, vr, k - cntl);
    }
    int query(int l, int r, int k) {
        return query(roots[l], roots[r + 1], 0, C - 1, k);
    }

    int update(int v, int vl, int vr, int ind, int x) {
        int newv = size(tree);
        tree.push_back(Node());
        if(vl == vr) {
            tree[newv].sm = tree[v].sm + x;
        }
        else {
            init_ch(v);
            tree[newv].l = tree[v].l;
            tree[newv].r = tree[v].r;
            int vm = (vl + vr) / 2;
            if(ind <= vm) tree[newv].l = update(tree[v].l, vl, vm, ind, x);
            else tree[newv].r = update(tree[v].r, vm + 1, vr, ind, x);
            tree[newv].sm = tree[tree[newv].l].sm + tree[tree[newv].r].sm;
        }
        return newv;
    }
};
