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

// Находит случайный отрицательный цикл в СВЯЗНОМ графе
vector<int> find_negative_cycle() {
    Ford_Bellman(0);
    for(int u = 0; u < n; ++u) {
        if(dist[u] == -LINF) {
            int v = u;
            for(int i = 0; i < n; ++i) v = pr[v];
            int vv = v;
            vector<int> ans;
            while(pr[v] != vv) {
                ans.push_back(v);
                v = pr[v];
            }
            ans.push_back(v);
            ans.push_back(ans[0]);
            reverse(all(ans));
            return ans;
        }
    }
    return {};
}
