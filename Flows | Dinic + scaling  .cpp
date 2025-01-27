// Пушка гонка, но зависит от величины макс потока
// O(n * m * log(U))

struct Dinic {
    int s, t, dist[mxN], ptr[mxN];
    Dinic(int s, int t) : s(s), t(t) {}

    bool bfs_dinic(ll mn) {
        fill(dist, dist + mxN, INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while(siz(q)) {
            int v = q.front(); q.pop();
            for(auto & [to, f, cap, obr] : g[v]) {
                if(f + mn <= cap && dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        return dist[t] != INF;
    }

    ll dfs_dinic(int v, ll flow, ll mn) {
        if(v == t) return flow;
        ll push = 0;
        for(int& i = ptr[v]; ptr[v] < siz(g[v]); ++ptr[v]) {
            int to = g[v][i].to, f = g[v][i].f, cap = g[v][i].cap, obr = g[v][i].obr;
            if(dist[to] == dist[v] + 1 && flow >= mn && f + mn <= cap) {
                int delta = dfs_dinic(to, min(flow, (ll)cap - f), mn);
                g[v][i].f += delta;
                g[to][obr].f -= delta;
                push += delta;
                flow -= delta;
                if(!flow) break;
            }
        }
        return push;
    }

    ll max_flow() {
        ll ans = 0;
        for(int k = 40; k >= 0; --k) {
            while (bfs_dinic(1ll << k)) {
                fill(ptr, ptr + mxN, 0);
                ans += dfs_dinic(s, LINF, 1ll << k);
            }
        }
        return ans;
    }
};
