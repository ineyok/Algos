// O(n ** 3)

// Кратчайшие пути между всеми парами вершин
// Можно любые ребра

ll dist[mxN][mxN];
int pr[mxN][mxN];
vector<pair<int, int>> g[mxN];
vector<int> get_path(int v, int to) {
    vector<int> path;
    while(v != to) {
        path.push_back(to);
        to = pr[v][to];
    }
    path.push_back(v);
    return path;
}
void Floyd() {
    for(int v = 0; v < mxN; ++v) {
        fill(dist[v], dist[v] + mxN, LINF);
        dist[v][v] = 0;
        for(auto & [to, w] : g[v]) dist[v][to] = min(dist[v][to], (ll)w);
    }
    for(int m = 0; m < mxN; ++m) {
        for (int v = 0; v < mxN; ++v) {
            for (int u = 0; u < mxN; ++u) {
                if(dist[v][u] > dist[v][m] + dist[m][u]) {
                    dist[v][u] = dist[v][m] + dist[m][u];
                    pr[v][u] = pr[m][u];
                }
            }
        }
    }
};
