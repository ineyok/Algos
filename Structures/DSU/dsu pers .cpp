// O(log2(n)) на запрос

// Персистентный СНМ
// Запросы и изменения к версии, создание новой версии из старой(изначально одна)

struct Segtree_pers {
    struct Node {
        int x;
        Node* l, * r;
        Node() : x(-1), l(0), r(0) {}
        Node(int x) : x(x), l(0), r(0) {}
        void build_ch() {
            if(!l) {
                l = new Node();
                r = new Node();
            }
        }
    };

    int n;
    vector<Node*> roots;

    Node* build(Node* v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            v->x = ar[vl];
            return v;
        }
        int vm = (vl + vr) / 2;
        v->build_ch();
        build(v->l, vl, vm, ar);
        build(v->r, vm + 1, vr, ar);
        return v;
    }

    Segtree_pers()=default;
    Segtree_pers(vector<int> & ar) : n((int)size(ar)) {
        roots.push_back(build(new Node(), 0, n - 1, ar));
    }

    int query(Node* v, int vl, int vr, int i) {
        if(vl == vr) return v->x;
        int vm = (vl + vr) / 2;
        if(i <= vm) return query(v->l, vl, vm, i);
        return query(v->r, vm + 1, vr, i);
    }
    int query(int vers, int i) { return query(roots[vers], 0, n - 1, i); }

    Node* update(Node* v, int vl, int vr, int i, int val) {
        if(vl == vr) {
            Node* newv = new Node(val);
            return newv;
        }
        int vm = (vl + vr) / 2;
        Node* newv = new Node();
        newv->l = v->l, newv->r = v->r;
        if(i <= vm) newv->l = update(v->l, vl, vm, i, val);
        else newv->r = update(v->r, vm + 1, vr, i, val);
        return newv;
    }
    Node* update(int vers, int i, int val) { return update(roots[vers], 0, n - 1, i, val); }
};

struct DSU_pers {
    int n;
    vector<int> cnt;
    Segtree_pers pr, sz;

    DSU_pers() = default;
    DSU_pers(int n) : n(n), cnt(1, n) {
        vector<int> vpr(n), vsz(n, 1);
        iota(vpr.begin(), vpr.end(), 0);
        pr = Segtree_pers(vpr), sz = Segtree_pers(vsz);
    }

    int root(int vers, int v) {
        int p = pr.query(vers, v);
        return (p == v ? v : root(vers, p));
    }
    bool connect(int vers, int a, int b) { return root(vers, a) == root(vers, b); }

    void merge(int vers, int a, int b) {
        a = root(vers, a), b = root(vers, b);
        if (a == b) return;
        int sza = sz.query(vers, a), szb = sz.query(vers, b);
        if (sza < szb) swap(a, b);
        sz.roots[vers] = sz.update(vers, a, sza + szb);
        pr.roots[vers] = pr.update(vers, b, a);
        cnt[vers]--;
    }

    int add_vers(int vers) {
        pr.roots.push_back(pr.roots[vers]);
        sz.roots.push_back(sz.roots[vers]);
        cnt.push_back(cnt[vers]);
        return (int)size(pr.roots) - 1;
    }
};
