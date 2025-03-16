// O(n + m)

// Мосты в графе

vector<pair<int, int>> br;
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
            if(up[to] > depth[v]) br.push_back({v, to});
        }
    }
}
// main()
for(int v = 0; v < n; ++v) {
    if(!used[v]) {
        dfs_br(v);
    }
}



// Точки сочленения в графе

vector<int> g[mxN];
int used[mxN], depth[mxN], up[mxN];
set<int> ap;

void dfs_ap(int v, int p = -1) {
    used[v] = 1;
    depth[v] = up[v] = (p >= 0 ? depth[p] + 1 : 1);
    int kids = 0;
    for (int to : g[v]) {
        if(to == p) continue;
        if(used[to]) {
            up[v] = min(up[v], depth[to]);
        }
        else {
            kids++;
            dfs_ap(to, v);
            up[v] = min(up[v], up[to]);
            if(up[to] >= depth[v] && p != -1) ap.insert(v);
        }
    }
    if(p == -1 && kids >= 2) ap.insert(v);
}
// main()
for(int v = 0; v < n; ++v) {
    if(!used[v]) {
        dfs_ap(v);
    }
}
