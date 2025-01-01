// Корневая декомпозиция массива
// ? кол-во элементов <x на отрезке [l, r]
// ! прибаление константы [l, r]

struct Sqrt_dec {
    int n, K;
    vector<ll> a, c;
    vector<vector<ll>> b;
    Sqrt_dec(vector<int> & ar) {
        int n = size(ar);
        K = 5e2;
        a.resize(n);
        b.resize(ceil(n, K));
        c.resize(size(b));
        for(int i = 0; i < n; ++i) {
            a[i] = ar[i];
            b[i / K].push_back(a[i]);
        }
        for(int i = 0; i < size(b); ++i)
            sort(all(b[i]));
    }
    
    int query(int l, int r, int x) {
        int lb = l / K, rb = r / K;
        int ans = 0;
        if(lb == rb) {
            for(int i = l; i <= r; ++i)
                ans += (a[i] + c[lb] < x);
        }
        else {
            for(int i = l; i < (lb + 1) * K; ++i)
                ans += (a[i] + c[lb] < x);
            for(int i = rb * K; i <= r; ++i)
                ans += (a[i] + c[rb] < x);
            for(int i = lb + 1; i < rb; ++i) {
                ans += lower_bound(all(b[i]), x - c[i]) - b[i].begin();
            }
        }
        return ans;
    }
    
    void add(int l, int r, int x) {
        int lb = l / K, rb = r / K;
        b[lb].clear();
        for(int i = lb * K; i < (lb + 1) * K; ++i) {
            if(l <= i && i <= r) a[i] += x;
            b[lb].push_back(a[i]);
        }
        sort(all(b[lb]));
        if(lb != rb) {
            b[rb].clear();
            for(int i = rb * K; i < (rb + 1) * K; ++i) {
                if(l <= i && i <= r) a[i] += x;
                b[rb].push_back(a[i]);
            }
            sort(all(b[rb]));
        }
        for(int i = lb + 1; i < rb; ++i)
            c[i] += x;
    }
};
