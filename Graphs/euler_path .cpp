// O(m * log(m))

// Эйлеров путь (мб цикл)

void dfs(int v, vector<map<int, int>>& gm, vector<int>& path) {
    while (gm[v].size()) {
        int to = gm[v].begin()->first;
        gm[v][to]--, gm[to][v]--;
        if (!gm[v][to]) {
            gm[v].erase(to);
            gm[to].erase(v);
        }
        dfs(to, gm, path);
    }
    path.push_back(v);
}

vector<int> euler_path(int n, int m) {
    vector<int> path;
    int start = 0;
    for(int v = 0; v < n; ++v) {
        if(siz(g[v]) % 2) start = v;
    }
    vector<map<int, int>> gm(n);
    for (int v = 0; v < n; ++v) {
        for (int to : g[v]) gm[v][to]++;
    }
    dfs(start, gm, path);
    if (path.size() < m + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
