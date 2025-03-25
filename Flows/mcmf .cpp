// O(n * m * U)
// O(m * log(m) * U) djikstra

// У ребёр появилась стоимость 1 одного потока по этому ребру
// Алгоритм поиска максимального потока минимальной стоимости (можно k-потока)
// Пускаем пути минимальной стоимости S -> T, пока можем (SPFA, потому что есть ребра отриц. стоимости)

struct MCMF {
    int inde[mxN], inq[mxN];
    ll dist[mxN], ans, flow;
    MCMF() {
        flow = ans = 0;
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
            flow += delta;
        }
    }

    bool spfa() {
        fill(dist, dist + mxN, LINF);
        fill(inq, inq + mxN, 0);
        dist[S] = 0;
        queue<int> q;
        q.push(S);
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
        return dist[T] != LINF;
    }
};


// Избавляемся от рёбер отрицательной стоимости, добавив потенциалы Джонсона для вершин
// Дейкстра вместо SPFA

struct MCMF {
    int inde[mxN];
    ll dist[mxN], pot[mxN], ans;
    MCMF() {
        ans = 0;
        while(djikstra()) {
            copy(dist, dist + mxN, pot);
            int delta = INF;
            for(int v = T; v != S; v = g[v][inde[v]].to) {
                int u = g[v][inde[v]].to, dir = g[v][inde[v]].obr;
                ckmin(delta, g[u][dir].cap - g[u][dir].f);
            }
            for(int v = T; v != S; v = g[v][inde[v]].to) {
                int u = g[v][inde[v]].to, dir = g[v][inde[v]].obr;
                g[u][dir].f += delta;
                g[v][inde[v]].f -= delta;
                ans += 1ll * delta * g[u][dir].cost;
            }
        }
    }

    bool djikstra() {
        fill(dist, dist + mxN, LINF);
        dist[S] = 0;
        set<pair<ll, int>> st;
        st.insert({0, S});
        while(siz(st)) {
            int v = st.begin()->second; st.erase(st.begin());
            for(auto & [to, f, cap, cost, obr] : g[v]) {
                if(f < cap && dist[to] > dist[v] + cost + pot[v] - pot[to]) {
                    st.erase({dist[to], to});
                    inde[to] = obr;
                    dist[to] = dist[v] + cost + pot[v] - pot[to];
                    st.insert({dist[to], to});
                }
            }
        }
        return dist[T] != LINF;
    }
};
