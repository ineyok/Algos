// Явное Декартово дерево
// ! добавить элемент X в множество
// ? сумма элементов множества от L до R по значению

struct Treap {
    struct Node {
        int x, y;
        ll sm;
        Node *l, *r;
        Node() : x(0), y(rnd()), sm(0), l(0), r(0) {}
        Node(int x) : x(x), y(rnd()), sm(x), l(0), r(0) {}
    };
    ll get_sm(Node *t) { return (t ? t->sm : 0); }
    Node *root;
    Treap() {
        root = new Node(-INF);
    }

    void update(Node * t) {
        if(!t) return;
        t->sm = t->x + get_sm(t->l) + get_sm(t->r);
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

    void insert(int x) {
        auto [t1, t] = split(root, x);
        auto [tx, t2] = split(t, x + 1);
        tx = new Node(x);
        root = merge(t1, merge(tx, t2));
    }

    ll query(int l, int r) {
        auto [t1, t] = split(root, l);
        auto [tq, t2] = split(t, r + 1);
        ll ans = get_sm(tq);
        root = merge(t1, merge(tq, t2));
        return ans;
    }
};
