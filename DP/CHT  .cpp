struct CHT {
    struct Line {
        ll k, c, start;
        int i;
        Line(ll k, ll c, ll start, int i) : k(k), c(c), start(start), i(i) {}
    };
    vector<Line> vec;

    CHT()=default;

    int query(ll x) {
        int lb = 0, rb = siz(vec);
        while(lb + 1 < rb) {
            int mid = (lb + rb) / 2;
            if(vec[mid].start <= x) lb = mid;
            else rb = mid;
        }
        return vec[lb].i;
    }

    void add(ll k, ll c, int i) {
        if(vec.empty()) {
            vec = {{k, c, -INF, i}};
        }
        else {
            ll xp = ceil(c - vec.back().c, vec.back().k - k);
            while (xp <= vec.back().start) {
                vec.pop_back();
                xp = ceil(c - vec.back().c, vec.back().k - k);
            }
            vec.push_back({k, c, xp, i});
        }
    }
};
