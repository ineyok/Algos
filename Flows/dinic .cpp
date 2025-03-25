// O(n**2 * m)

// Алгоритм Диница, реализованный структурой
// Строит слоистую сеть и для каждой ищет блокирующий поток с помощью dfs

struct Dinic {
    int dist[mxN], ptr[mxN];
    ll ans;
    Dinic() {
        ans = 0;
        while(bfs()) {
            fill(ptr, ptr + mxN, 0);
            ll delta = dfs(S, LINF);
            if(!delta) break;
            ans += delta;
        }
    }

    bool bfs() {
        fill(dist, dist + mxN, INF);
        dist[S] = 0;
        queue<int> q;
        q.push(S);
        while(siz(q)) {
            int v = q.front(); q.pop();
            for(auto & [to, f, cap, obr] : g[v]) {
                if(f < cap && dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }
        return dist[T] != INF;
    }

    ll dfs(int v, ll flow) {
        if(v == T) return flow;
        ll push = 0;
        for(int & i = ptr[v]; ptr[v] < siz(g[v]); ++ptr[v]) {
            int to = g[v][i].to, f = g[v][i].f, cap = g[v][i].cap, obr = g[v][i].obr;
            if(dist[to] == dist[v] + 1 && f < cap) {
                int delta = dfs(to, min(flow, (ll)cap - f));
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
