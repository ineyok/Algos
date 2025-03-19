// O(n + m)

// Точки сочленения
int used[mxN], depth[mxN], up[mxN];
set<int> ap;
void dfs_ap(int v, int p = -1) {
    used[v] = 1;
    depth[v] = up[v] = (p >= 0 ? depth[p] + 1 : 0);
    int kids = 0;
    for(int to : g[v]) {
        if(to == p) continue;
        if(used[to]) {
            up[v] = min(up[v], depth[to]);
        }
        else {
            kids++;
            dfs_ap(to, v);
            up[v] = min(up[v], up[to]);
            if(p != -1 && up[to] >= depth[v]) ap.insert(v);
        }
    }
    if(p == 1 && kids > 1) ap.insert(v);
}

// Покраска ребёр по компонентам вершинной двусвязности
map<pair<int, int>, int> clr;
int mxc;
void dfs_paint(int v, int p, int color) {
    used[v] = 1;
    for(int to : g[v]) {
        if(to == p) continue;
        if(used[to] && depth[to] < depth[v]) {
            clr[{v, to}] = clr[{to, v}] = color;
        }
        else if(!used[to]) {
            if(up[to] >= depth[v]) {
                mxc++;
                clr[{v, to}] = clr[{to, v}] = mxc;
                dfs_paint(to, v, mxc);
            }
            else {
                clr[{v, to}] = clr[{to, v}] = color;
                dfs_paint(to, v, color);
            }
        }
    }
}
