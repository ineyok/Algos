// Merge Sort Tree, в каждой вершине Treap
// ? кол-во элементов <x на отрезке
// ! изменение в точке

struct Treap {
    struct Node {
        int x, y, cnt, sum;
        Node *l, *r;
        Node() : x(-INF), y(rnd()), cnt(0), sum(0), l(0), r(0) {}
    };
    int get_sum(Node *t) { return (t ? t->sum : 0); }
    void update(Node *t) {
        t->sum = t->cnt + get_sum(t->l) + get_sum(t->r);
    }
    Node *root;
    Treap() {
        root = nullptr;
    }

    Node *merge(Node *t1, Node *t2) {
        if(!t1) return t2;
        if(!t2) return t1;
        if(t1->y > t2->y) {
            t1->r = merge(t1->r, t2);
            update(t1);
            return t1;
        }
        else {
            t2->l = merge(t1, t2->l);
            update(t2);
            return t2;
        }
    }

    pair<Node*, Node*> split(Node *t, int x) {
        if(!t) return {nullptr, nullptr};
        if(t->x >= x) {
            auto [t1, t2] = split(t->l, x);
            t->l = t2;
            update(t);
            return {t1, t};
        }
        else {
            auto [t1, t2] = split(t->r, x);
            t->r = t1;
            update(t);
            return {t, t2};
        }
    }

    int query(int x) {
        auto [t1, t2] = split(root, x);
        int ans = (t1 ? t1->sum : 0);
        root = merge(t1, t2);
        return ans;
    }

    void update(int x, int diff) {
        auto [t1, t] = split(root, x);
        auto [tx, t2] = split(t, x + 1);
        int cur = (tx ? tx->cnt : 0);
        tx = new Node();
        tx->x = x;
        tx->cnt = tx->sum = cur + diff;
        root = merge(t1, merge(tx, t2));
    }

    vector<pair<int, int>> traver() {
        vector<pair<int, int>> vec;
        auto dfs = [&](auto &&self, Node *v) -> void {
            if(v == nullptr) return;
            if(v->l) self(self, v->l);
            vec.push_back({v->x, v->cnt});
            if(v->r) self(self, v->r);
        };
        dfs(dfs, root);
        return vec;
    }
};

struct MST_with_Treap {
    int n;
    vector<Treap> tree;
    void build(int v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            tree[v].update(ar[vl], 1);
            return;
        }
        int vm = (vl + vr) / 2;
        build(v * 2 + 1, vl, vm, ar);
        build(v * 2 + 2, vm + 1, vr, ar);
        for(auto [x, cnt] : tree[v * 2 + 1].traver()) {
            tree[v].update(x, cnt);
        }
        for(auto [x, cnt] : tree[v * 2 + 2].traver()) {
            tree[v].update(x, cnt);
        }
    }
    MST_with_Treap(vector<int> & ar) {
        n = size(ar);
        tree.resize(n * 4);
        build(0, 0, n - 1, ar);
    }

    int query(int v, int vl, int vr, int l, int r) {
        if(r < vl || vr < l) return 0;
        if(l <= vl && vr <= r) { return tree[v].query(l); }
        int vm = (vl + vr) / 2;
        return query(v * 2 + 1, vl, vm, l, r) + query(v * 2 + 2, vm + 1, vr, l, r);
    }
    int query(int l, int r) { return query(0, 0, n - 1, l, r); }

    void update(int v, int vl, int vr, int i, int xp, int xm) {
        tree[v].update(xp, 1);
        tree[v].update(xm, -1);
        if(vl == vr) return;
        int vm = (vl + vr) / 2;
        if(i <= vm) update(v * 2 + 1, vl, vm, i, xp, xm);
        else update(v * 2 + 2, vm + 1, vr, i, xp, xm);
    }
    void update(int i, int xp, int xm) { update(0, 0, n - 1, i, xp, xm); }
};


// main()

int n, q;
cin >> n;
vector<int> a(n), b(n);
map<int, set<int>> mp;
for(int i = 0; i < n; ++i) {
    cin >> a[i];
    if(mp[a[i]].empty()) mp[a[i]].insert(-1);
    b[i] = *mp[a[i]].rbegin();
    mp[a[i]].insert(i);
}
MST_with_Treap segt(b);
cin >> q;
while(q--) {
    char tp;
    cin >> tp;
    if(tp == '?') {
        int l, r;
        cin >> l >> r; l--; r--;
        cout << segt.query(l, r) << '\n';
    }
    else {
        int i, x;
        cin >> i >> x; i--;
        mp[a[i]].erase(i);
        auto it = mp[a[i]].upper_bound(i);
        if(it != mp[a[i]].end()) {
            int nxt = *it, prev = *(--it);
            segt.update(nxt, prev, b[nxt]);
            b[nxt] = prev;
        }
        if(mp[x].empty()) mp[x].insert(-1);
        it = mp[x].upper_bound(i);
        if(it != mp[x].end()) {
            int nxt = *it;
            segt.update(nxt, i, b[nxt]);
            b[nxt] = i;
        }
        int prev = *(--it);
        segt.update(i, prev, b[i]);
        b[i] = prev;
        a[i] = x;
        mp[a[i]].insert(i);
    }
}
