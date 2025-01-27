// Алгоритм Диница, реализованный структурой
// Строит слоистую сеть и для каждой ищет блокирующий поток с помощью dfs
// Две оптимизации: строки (30), (38)
// O(n**2 * m)

struct Dinic {
    int s, t, dist[mxN], ptr[mxN];
    Dinic(int s, int t) : s(s), t(t) {}

    bool bfs_dinic() {
        fill(dist, dist + mxN, INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        while(siz(q)) {
            int v = q.front(); q.pop();
            for(auto & [to, f, cap, obr] : g[v]) {
                if(f < cap && dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        return dist[t] != INF;
    }

    ll dfs_dinic(int v, ll flow) {
        if(v == t) return flow;
        ll push = 0;
        for(int& i = ptr[v]; ptr[v] < siz(g[v]); ++ptr[v]) {
            int to = g[v][i].to, f = g[v][i].f, cap = g[v][i].cap, obr = g[v][i].obr;
            if(dist[to] == dist[v] + 1 && f < cap) {
                int delta = dfs_dinic(to, min(flow, (ll)cap - f));
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
        while(bfs_dinic()) {
            fill(ptr, ptr + mxN, 0);
            ans += dfs_dinic(s, LINF);
        }
        return ans;
    }
};
