// O(|F|*(n+m))
// O(m**2 * log(|F|)) scaling

// Алгоритм Форда-Фалкерсона поиска максимального потока в графе
// Находит какой-нибудь увеличивающий путь в остаточной сети из s -> t

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


// Алгоритм Форда Фалкерсона с масштабированием
// Пытаемся найти увеличивающий путь потоком не менее 2**k, если не можешь уменьшаем k

int used[mxN];
int dfs_ff(int v, int t, int flow, int mn) {
    used[v] = 1;
    if(v == t) return flow;
    for(auto & [to, f, cap, obr] : g[v]) {
        if(!used[to] && f + mn <= cap) {
            int delta = dfs_ff(to, t, min(flow, cap - f), mn);
            if(delta) {
                f += delta;
                g[to][obr].f -= delta;
                return delta;
            }
        }
    }
    return 0;
}
ll ford_fulkerson_scaling(int s, int t) {
    ll ans = 0, cur;
    for(int k = 30; k >= 0; --k) {
        fill(used, used + mxN, 0);
        while((cur = dfs_ff(s, t, INF, 1 << k))) {
            ans += cur;
            fill(used, used + mxN, 0);
        }
    }
    return ans;
}
