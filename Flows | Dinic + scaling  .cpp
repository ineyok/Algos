// Пушка гонка, но зависит от величины макс потока
// O(n * m * log(U))

struct Dinic {
    int dist[mxN], ptr[mxN];
    ll ans;
    Dinic() {
        ans = 0;
        for(int k = 30; k >= 0; --k) {
            while(bfs(1 << k)) {
                fill(ptr, ptr + mxN, 0);
                ll delta = dfs(S, LINF, 1 << k);
                if (!delta) break;
                ans += delta;
            }
        }
    }

    bool bfs(int mn) {
        fill(dist, dist + mxN, INF);
        dist[S] = 0;
        queue<int> q;
        q.push(S);
        while(siz(q)) {
            int v = q.front(); q.pop();
            for(auto & [to, f, cap, obr] : g[v]) {
                if(f + mn <= cap && dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        return dist[T] != INF;
    }

    ll dfs(int v, ll flow, int mn) {
        if(v == T) return flow;
        ll push = 0;
        for(int & i = ptr[v]; ptr[v] < siz(g[v]); ++ptr[v]) {
            int to = g[v][i].to, f = g[v][i].f, cap = g[v][i].cap, obr = g[v][i].obr;
            if(dist[to] == dist[v] + 1 && f + mn <= cap) {
                int delta = dfs(to, min(flow, (ll)cap - f), mn);
                g[v][i].f += delta;
                g[to][obr].f -= delta;
                push += delta;
                flow -= delta;
                if(!flow) break;
            }
        }
        return push;
    }
};
