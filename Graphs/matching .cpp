// O(n * m), по факту сильно быстрее

// Максимальное паросочетание в двудольном графе
// Алгоритм Куна

int used[mxN * 2], mt[mxN * 2], vers = 0;

bool dfs(int v) {
    if(used[v] == vers) return 0;
    used[v] = vers;
    for(int to : g[v]) {
        if(mt[to] == -1) {
            mt[to] = v;
            return 1;
        }
    }
    for(int to : g[v]) {
        if(dfs(mt[to])) {
            mt[to] = v;
            return 1;
        }
    }
    return 0;
}
int kuhn() {
    int ans = 0;
    fill(mt, mt + mxN * 2, -1);
    for(int v = 0; v < m; ++v) {
        vers++;
        if(dfs(v)) ans++;
    }
    return ans;
}
