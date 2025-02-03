// Избавляемся от рёбер отрицательной стоимости, добавив потенциалы Джонсона для вершин
// Дейкстра вместо SPFA
// O(m * log(m) * U)

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
