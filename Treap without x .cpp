// Неявное Декартово дерево на массиве
// ? Минимум на отрезке индексов [l, r]
// ! Разворот отрезка
// ! Прибавление на отрезке

struct Treap {
    struct Node {
        int x, y, sz, mn, lazy_rev, lazy_add;
        Node *l, *r;
        Node() {}
        Node(int x) : x(x), y(rnd()), sz(1), mn(x), lazy_rev(0), l(0), r(0) {}
    };
    int get_sz(Node * t) { return (t ? t->sz : 0); }
    int get_mn(Node * t) { return (t ? t->mn : INF); }

    void push(Node * t) {
        if(!t) return;
        t->mn += t->lazy_add;
        if(t->l) t->l->lazy_add += t->lazy_add;
        if(t->r) t->r->lazy_add += t->lazy_add;
        t->lazy_add = 0;
        if(t->lazy_rev) {
            swap(t->l, t->r);
            if(t->l) t->l->lazy_rev ^= 1;
            if(t->r) t->r->lazy_rev ^= 1;
            t->lazy_rev = 0;
        }
    }

    void update(Node * t) {
        if(!t) return;
        t->sz = get_sz(t->l) + get_sz(t->r) + 1;
        t->mn = min({t->x, get_mn(t->l), get_mn(t->r)});
    }

    Node *root;
    Treap(vector<int> & ar) {
        root = nullptr;
        for(int el : ar) {
            root = merge(root, new Node(el));
        }
    }

    Node * merge(Node *t1, Node *t2) {
        if(!t1) return t2;
        if(!t2) return t1;
        if(t1->y > t2->y) {
            push(t1);
            t1->r = merge(t1->r, t2);
            update(t1);
            return t1;
        }
        else {
            push(t2);
            t2->l = merge(t1, t2->l);
            update(t2);
            return t2;
        }
    }

    pair<Node*, Node*> split(Node *t, int sz) {
        if(!t) return {nullptr, nullptr};
        push(t);
        if(get_sz(t->l) >= sz) {
            auto [t1, t2] = split(t->l, sz);
            t->l = t2;
            update(t);
            return {t1, t};
        }
        else {
            auto [t1, t2] = split(t->r, sz - get_sz(t->l) - 1);
            t->r = t1;
            update(t);
            return {t, t2};
        }
    }

    int query(int l, int r) {
        auto [t, t2] = split(root, r + 1);
        auto [t1, tq] = split(t, l);
        int ans = get_mn(tq);
        root = merge(merge(t1, tq), t2);
        return ans;
    }

    void reverse(int l, int r) {
        auto [t, t2] = split(root, r + 1);
        auto [t1, tq] = split(t, l);
        tq->lazy_rev ^= 1;
        root = merge(merge(t1, tq), t2);
    }

    void add(int l, int r, int x) {
        auto [t, t2] = split(root, r + 1);
        auto [t1, tq] = split(t, l);
        tq->lazy_add += x;
        root = merge(merge(t1, tq), t2);
    }
};
