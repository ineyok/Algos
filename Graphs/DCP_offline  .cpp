// O(k * log2(k))

// Дано k запросов вида (a, b):
// 1 - добавить ребро
// 0 - удалить ребро
// 2 - связаны ли вершины

struct DSU_o {
    ...
};

struct DCP_offline {
    int k;
    vector<vector<pair<int, int>>> edges;
    vector<pair<int, int>> info;
    vector<int> ans;
    DSU_o dsu;

    void add_info(int v, int vl, int vr, int l, int r, pair<int, int> val) {
        if (r < vl || vr < l) return;
        if (l <= vl && vr <= r) {
            info[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        add_info(v * 2 + 1, vl, vm, l, r, val);
        add_info(v * 2 + 2, vm + 1, vr, l, r, val);
    }
    void add_info(int l, int r, pair<int, int> val) { add_info(0, 0, k - 1, l, r, val); }

    void add_edge(int v, int vl, int vr, int l, int r, pair<int, int> val) {
        if(r < vl || vr < l) return;
        if(l <= vl && vr <= r) {
            edges[v].push_back(val);
            return;
        }
        int vm = (vl + vr) / 2;
        add_edge(v * 2 + 1, vl, vm, l, r, val);
        add_edge(v * 2 + 2, vm + 1, vr, l, r, val);
    }
    void add_edge(int l, int r, pair<int, int> val) { add_edge(0, 0, k - 1, l, r, val); }

    void rec(int v, int vl, int vr) {
        dsu.add_vers();
        for(auto & [a, b] : edges[v]) dsu.merge(a, b);
        if(vl == vr) {
            if(info[v].first != -1) {
                int a = info[v].first, b = info[v].second;
                ans.push_back(dsu.connect(a, b));
            }
            dsu.del_vers();
            return;
        }
        int vm = (vl + vr) / 2;
        rec(v * 2 + 1, vl, vm);
        rec(v * 2 + 2, vm + 1, vr);
        dsu.del_vers();
    }

    DCP_offline(int n, vector<vector<int>> &zap) : k(siz(zap)) {
        edges.resize(k * 4);
        info.resize(k * 4, {-1, -1});
        dsu = DSU_o(n);
        map<pair<int, int>, int> mp_l;
        for(int i = 0; i < siz(zap); ++i) {
            int tp = zap[i][0], v = zap[i][1], u = zap[i][2];
            if(v > u) swap(v, u);
            if(tp == 2) {
                add_info(i, i, {v, u});
            }
            else if(tp == 1) {
                mp_l[{v, u}] = i;
            }
            else {
                add_edge(mp_l[{v, u}], i, {v, u});
                mp_l.erase({v, u});
            }
        }
        for(auto & el : mp_l) {
            add_edge(el.second, k - 1, el.first);
        }
        rec(0, 0, k - 1);
    }
};
