// O(n * sqrt(n))

// МО на дереве - Веса на рёбрах

vector<pair<int, int>> g[mxN];
vector<int> order;
map<pair<int, int>, int> mp;
int n, pos[mxN], cnt[mxN];
vector<vector<int>> edges;

void dfs(int v, int p = 0) {
    pos[v] = siz(order);
    for(auto & [to, x] : g[v]) {
        if(to != p) {
            order.push_back(mp[{v, to}]);
            dfs(to, v);
            order.push_back(mp[{to, v}]);
        }
    }
}

void func(int i) {
    int num = order[i];
    if(!cnt[num]) {
        // add edges[num]
    }
    else {
        // del edges[num]
    }
    cnt[num] ^= 1;
}

// main()
dfs(0);
vector<vector<int>> zap(q);
for(int i = 0; i < q; ++i) {
    int v, u;
    cin >> v >> u, v--, u--;
    int l = pos[v], r = pos[u];
    if(l > r) swap(l, r);
    r--;
    zap[i] = {l, r, i};
}
sort(all(zap), [&](vector<int> & a, vector<int> & b) {
    if(a[0] / K != b[0] / K) return a[0] < b[0];
    return a[1] < b[1];
});
int l = 0, r = -1;
vector<int> ans(q);
for(auto & el : zap) {
    int nl = el[0], nr = el[1], ind = el[2];
    while(nl < l) {
        l--;
        func(l);
    }
    while(r < nr) {
        r++;
        func(r);
    }
    while(l < nl) {
        func(l);
        l++;
    }
    while(nr < r) {
        func(r);
        r--;
    }
    ans[ind] = ...
}



// МО на дереве - Веса на вершинах

vector<int> g[mxN], euler;
int fst[mxN], lst[mxN], timer = -1, total_cnt[mxN], cnt[mxN];
void dfs(int v, int p) {
    fst[v] = ++timer;
    fst[v] = siz(euler);
    euler.push_back(v);
    total_cnt[v]++;
    for(int to : g[v]) {
        if(to == p) continue;
        dfs(to, v);
        lst[v] = siz(euler);
        euler.push_back(v);
        total_cnt[v]++;
    }
    if(v && siz(g[v]) == 1) {
        lst[v] = siz(euler);
        euler.push_back(v);
        total_cnt[v]++;
    }
}

void add(int i) {
    int v = euler[i];
    if(!cnt[v]) {
        // add v
    }
    else if(cnt[v] + 1 == total_cnt[v]) {
        // del v
    }
    cnt[v]++;
}

void del(int i) {
    int v = euler[i];
    if(cnt[v] == total_cnt[v]) {
        // add v
    }
    else if(cnt[v] == 1) {
        // del v
    }
    cnt[v]--;
}

//main()
vector<vector<int>> zap(q);
for(int i = 0; i < q; ++i) {
    int v, u;
    cin >> v >> u, v--, u--;
    int l, r;
    if(fst[v] < fst[u]) {
        l = fst[v], r = fst[u];
        if(lst[v] < fst[u]) l++;
    }
    else {
        l = fst[u], r = fst[v];
        if(lst[u] < fst[v]) l++;
    }
    zap[i] = {l, r, i};
}
//...
