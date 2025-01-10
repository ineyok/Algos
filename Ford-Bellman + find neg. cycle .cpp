// O(V * E)


// Находит кратчайшие расстояния от одной вершины до всех остальных в !графе с отрицательными циклами!
// Расстояние до вершин, достижимых из отрицательных циклов, равно -LINF
ll dp[mxN];
int pr[mxN], n;
vector<vector<int>> edges;
void Ford_Bellman(int start) {
    fill(dist, dist + mxN, LINF);
    dist[start] = 0;
    for(int i = 0; i < n; ++i) {
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
ll dp[mxN];
int pr[mxN], n;
vector<vector<int>> edges;
vector<int> find_negative_cycle() {
    fill(dp, dp + mxN, 0);
    for(int i = 0; i < n; ++i) {
        for (auto &el: edges) {
            int v = el[0], to = el[1], w = el[2];
            if (dp[to] > dp[v] + w) {
                dp[to] = dp[v] + w;
                pr[to] = v;
            }
        }
    }
    for(auto & el : edges) {
        int u = el[0], v = el[1], w = el[2];
        if(dp[v] > dp[u] + w) {
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
