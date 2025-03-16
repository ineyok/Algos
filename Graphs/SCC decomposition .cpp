// O(n + m)

// Поиск Компонент сильной связности в ориентированном графе

int n, used[mxN], scc[mxN];
vector<int> g[mxN], gr[mxN], order;

void topsort(int v) {
    if(used[v]) return;
    used[v] = 1;
    for(int to : g[v]) topsort(to);
    order.push_back(v);
}

void dfs_comp(int v, int k) {
    if(scc[v]) return;
    scc[v] = k;
    for(int to : gr[v]) dfs_comp(to, k);
}

void scc_decomposition() {
    for(int v = 0; v < n; ++v) {
        if(!used[v]) {
            topsort(v);
        }
    }
    reverse(all(order));
    int k = 0;
    for(int v : order) {
        if(!scc[v]) {
            dfs_comp(v, ++k);
        }
    }
}
