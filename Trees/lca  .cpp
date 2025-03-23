// O(log(n)) на запрос

// Lca(v, u) в дереве

int up[mxN][LG], tin[mxN], tout[mxN], timer = -1;

void dfs(int v, int p = 0) {
    tin[v] = ++timer;
    up[v][0] = p;
    for(int i = 1; i < LG; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for(int to : g[v]) {
        if(to != p) dfs(to, v);
    }
    tout[v] = timer;
}

bool is_parent(int p, int v) { return (tin[p] <= tin[v] && tout[v] <= tout[p]); }
int find_lca(int a, int b) {
    if(is_parent(a, b)) return a;
    for(int i = LG - 1; i >= 0; --i) {
        if(!is_parent(up[a][i], b)) a = up[a][i];
    }
    return up[a][0];
}
