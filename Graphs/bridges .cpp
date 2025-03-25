// O(n + m)

// Мосты в графе

set<pair<int, int>> br;
int used[mxN], depth[mxN], up[mxN];

void dfs_br(int v, int p = -1) {
    used[v] = 1;
    depth[v] = up[v] = (p >= 0 ? depth[p] + 1 : 1);
    for(int to : g[v]) {
        if(to == p) continue;
        if(used[to]) {
            up[v] = min(up[v], depth[to]);
        }
        else {
            dfs_br(to, v);
            up[v] = min(up[v], up[to]);
            if(up[to] > depth[v]) br.insert({v, to});
        }
    }
}
// main()
for(int v = 0; v < n; ++v) {
    if(!used[v]) {
        dfs_br(v);
    }
}


// Компоненты реберной двусвязности

int comp[mxN];
void dfs_comp(int v, int k) {
    if(comp[v]) return;
    comp[v] = k;
    for(int to : g[v]) {
        if(br.find({v, to}) == br.end() && br.find({to, v}) == br.end()) {
            dfs_comp(to, k);
        }
    }
}
// main()
k = 0;
for(int v = 0; v < n; ++v) {
    if(!comp[v]) dfs_comp(v, ++k);
}
