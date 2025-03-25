// O(log(n)) на запрос

// min= на отрезке

struct JiDriver {
    int n;
    vector<int> mx1, mx2, mxcnt, lazy;
    vector<ll> sm;
    void merge(int v) {
        mx1[v] = max(mx1[v * 2 + 1], mx1[v * 2 + 2]);
        sm[v] = sm[v * 2 + 1] + sm[v * 2 + 2];
        if(mx1[v * 2 + 1] > mx1[v * 2 + 2]) {
            mxcnt[v] = mxcnt[v * 2 + 1];
            mx2[v] = max(mx2[v * 2 + 1], mx1[v * 2 + 2]);
        }
        else if(mx1[v * 2 + 1] < mx1[v * 2 + 2]) {
            mxcnt[v] = mxcnt[v * 2 + 2];
            mx2[v] = max(mx1[v * 2 + 1], mx2[v * 2 + 2]);
        }
        else {
            mxcnt[v] = mxcnt[v * 2 + 1] + mxcnt[v * 2 + 2];
            mx2[v] = max(mx2[v * 2 + 1], mx2[v * 2 + 2]);
        }
    }

    void build(int v, int vl, int vr, vector<int> & ar) {
        if(vl == vr) {
            mx1[v] = sm[v] = ar[vl];
            mxcnt[v] = 1;
            return;
        }
        int vm = (vl + vr) / 2;
        build(v * 2 + 1, vl, vm, ar);
        build(v * 2 + 2, vm + 1, vr, ar);
        merge(v);
    }
    JiDriver(vector<int> & ar) {
        n = size(ar);
        mx1.resize(n * 4);
        mx2.resize(n * 4, -INF);
        mxcnt.resize(n * 4);
        lazy.resize(n * 4, -INF);
        sm.resize(n * 4, 0);
        build(0, 0, n - 1, ar);
    }

    void push(int v, int vl, int vr) {
        if(lazy[v] > mx1[v]) lazy[v] = -INF;
        if(lazy[v] == -INF) return;
        sm[v] += 1ll * (lazy[v] - mx1[v]) * mxcnt[v];
        mx1[v] = lazy[v];
        if(vl != vr) {
            lazy[v * 2 + 1] = lazy[v];
            lazy[v * 2 + 2] = lazy[v];
        }
        lazy[v] = -INF;
    }

    ll query(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if(r < vl || vr < l) return 0;
        if(l <= vl && vr <= r) return sm[v];
        int vm = (vl + vr) / 2;
        return query(v * 2 + 1, vl, vm, l, r) + query(v * 2 + 2, vm + 1, vr, l, r);
    }
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }

    void update_min(int v, int vl, int vr, int l, int r, int x) {
        push(v, vl, vr);
        if(r < vl || vr < l || mx1[v] <= x) return;
        if(l <= vl && vr <= r && mx2[v] <= x) {
            lazy[v] = x;
            push(v, vl, vr);
            return;
        }
        int vm = (vl + vr) / 2;
        update_min(v * 2 + 1, vl, vm, l, r, x);
        update_min(v * 2 + 2, vm + 1, vr, l, r, x);
        merge(v);
    }
    void update_min(int l, int r, int x) { update_min(0, 0, n - 1, l, r, x); }
};
