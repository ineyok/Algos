// O(log2(n)) на запрос

// Heavy-light decomposition

int sz[mxN], pr[mxN], bg[mxN], tin[mxN], timer = -1;

void dfs_sz(int v, int p) {
    pr[v] = p;
    sz[v] = 1;
    for(int to : g[v]) {
        if(to != p) {
            dfs_sz(to, v);
            sz[v] += sz[to];
        }
    }
}
void dfs_hld(int v, int p = 0, int b = 0) {
    tin[v] = ++timer;
    bg[v] = b;
    sort(all(g[v]), [&](int a, int b) {
        return sz[a] > sz[b];
    });
    if(siz(g[v]) && g[v][0] == p) g[v].erase(g[v].begin());
    if(siz(g[v])) dfs_hld(g[v][0], v, b);
    for(int i = 1; i < siz(g[v]); ++i) dfs_hld(g[v][i], v, g[v][i]);
}

int query_hld(int v, int u) {
    int ans;
    while(bg[v] != bg[u]) {
        if(tin[bg[v]] < tin[bg[u]]) swap(v, u);
        // ans <- struct.query(tin[bg[v]], tin[v])
        v = pr[bg[v]];
    }
    if(tin[v] > tin[u]) swap(v, u);
    // ans <- struct.query(tin[v], tin[u])
    return ans;
}
void update_hld(int v, int u) {
    while(bg[v] != bg[u]) {
        if(tin[bg[v]] < tin[bg[u]]) swap(v, u);
        // struct.update(tin[bg[v]], tin[v])
        v = pr[bg[v]];
    }
    if(tin[v] > tin[u]) swap(v, u);
    // struct.update(tin[v], tin[u])
}
