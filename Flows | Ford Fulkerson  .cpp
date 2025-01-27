// Алгоритм Форда-Фалкерсона поиска максимального потока в графе
// Находит какой-нибудь увеличивающий путь в остаточной сети из s -> t
// O(|F|*(n+m))

int used[mxN];
int dfs_ff(int v, int t, int flow) {
    used[v] = 1;
    if(v == t) return flow;
    for(auto & [to, f, cap, obr] : g[v]) {
        if(!used[to] && f < cap) {
            int delta = dfs_ff(to, t, min(flow, cap - f));
            if(delta) {
                f += delta;
                g[to][obr].f -= delta;
                return delta;
            }
        }
    }
    return 0;
}
ll ford_fulkerson(int s, int t) {
    ll ans = 0, cur;
    while((cur = dfs_ff(s, t, INF))) {
        ans += cur;
        fill(used, used + mxN, 0);
    }
    return ans;
}
