// O((n + m) * log(n))

// Центроидная декомпозиция
vector<int> g[mxN], order;
int lvl[mxN], cent[mxN][LG], sz[mxN];

void dfs1(int v, int p = -1) {
    if(lvl[v]) {
        sz[v] = 0;
        return;
    }
    sz[v] = 1;
    for(int to : g[v]) {
        if(to != p) {
            dfs1(to, v);
            sz[v] += sz[to];
        }
    }
    order.push_back(v);
}
void dfs2(int v, int c, int p = -1) {
    if(lvl[v] && v != c) return;
    cent[v][lvl[c]] = c;
    for(int to : g[v]) {
        if(to != p) dfs2(to, c, v);
    }
}
void build_ctd(int v = 0, int l = 1) {
    order.clear();
    dfs1(v);
    for(int u : order) {
        if(sz[u] > sz[v] / 2) {
            v = u;
            break;
        }
    }
    lvl[v] = l;
    dfs2(v, v);
    for(int u : g[v]) {
        if(!lvl[u]) build_ctd(u, l + 1);
    }
}
