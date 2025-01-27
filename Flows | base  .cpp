// Структура ребра и базовые функции для потоков

struct Edge {
    int to, f, cap, obr;
};
vector<Edge> g[mxN];
void add_edge(int v, int to, int cap) {
    g[v].push_back({to, 0, cap, siz(g[to])});
    g[to].push_back({v, 0, 0, siz(g[v]) - 1});
}

void add_undir_edge(int v, int u, int cap) {
    g[v].push_back({u, 0, cap, siz(g[u])});
    g[u].push_back({v, 0, cap, siz(g[v]) - 1});
}
