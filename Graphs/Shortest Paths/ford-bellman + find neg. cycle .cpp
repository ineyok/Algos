// O(V * E)

// Находит кратчайшие расстояния от одной вершины до всех остальных в !графе с отрицательными циклами!
// Расстояние до вершин, достижимых из отрицательных циклов, равно -LINF

ll dist[mxN];
int pr[mxN], n;
vector<vector<int>> edges;
void Ford_Bellman(int start) {
    fill(dist, dist + mxN, LINF);
    dist[start] = 0;
    for(int i = 0; i < n - 1; ++i) {
        for (auto &el : edges) {
            int v = el[0], to = el[1], w = el[2];
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                pr[to] = v;
            }
        }
    }
    for(auto & el : edges) {
        int v = el[0], to = el[1], w = el[2];
        if (dist[to] > dist[v] + w) {
            dist[to] = -LINF;
        }
    }
}


// Находит случайный отрицательный цикл в графе
// (Запускаем Ford_B от всех вершин)

ll dist[mxN];
int pr[mxN], n;
vector<vector<int>> edges;
vector<int> find_neg_cycle() {
    fill(dist, dist + mxN, 0);
    for(int i = 0; i < n - 1; ++i) {
        for (auto &el : edges) {
            int v = el[0], to = el[1], w = el[2];
            if (dist[to] > dist[v] + w) {
                dist[to] = dist[v] + w;
                pr[to] = v;
            }
        }
    }
    for(auto & el : edges) {
        int v = el[0], to = el[1], w = el[2];
        if(dist[to] > dist[v] + w) {
            for(int i = 0; i < n - 1; ++i) v = pr[v];
            int vv = v;
            vector<int> cycle;
            while(cycle.empty() || v != vv) {
                cycle.push_back(v);
                v = pr[v];
            }
            reverse(all(cycle));
            return cycle;
        }
    }
    return {};
}
