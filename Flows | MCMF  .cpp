// У ребёр появилась стоимость 1 одного потока по этому ребру
// Алгоритм поиска максимального потока минимальной стоимости (можно k-потока)
// Пускаем пути минимальной стоимости S -> T, пока можем (SPFA, потому что есть ребра отриц. стоимости)
// O(n * m * U)

struct MCMF {
    int dist[mxN], inde[mxN], inq[mxN];
    ll ans;
    MCMF() {
        ans = 0;
        while(spfa()) {
            int delta = INF;
            for(int v = T; v != S; v = g[v][inde[v]].to) {
                int u = g[v][inde[v]].to, dir = g[v][inde[v]].obr;
                ckmin(delta, g[u][dir].cap - g[u][dir].f);
            }
            for(int v = T; v != S; v = g[v][inde[v]].to) {
                int u = g[v][inde[v]].to, dir = g[v][inde[v]].obr;
                g[u][dir].f += delta;
                g[v][inde[v]].f -= delta;
            }
            ans += 1ll * delta * dist[T];
        }
    }

    bool spfa() {
        fill(dist, dist + mxN, INF);
        fill(inq, inq + mxN, 0);
        dist[S] = 0;
        queue<int> q; q.push(S);
        while(siz(q)) {
            int v = q.front(); q.pop();
            inq[v] = 0;
            for(auto & [to, f, cap, cost, obr] : g[v]) {
                if(f < cap && ckmin(dist[to], dist[v] + cost)) {
                    inde[to] = obr;
                    if(!inq[to]) q.push(to);
                    inq[to] = 1;
                }
            }
        }
        return dist[T] != INF;
    }
};
