// O(V * E)

// Для графов с отриц. ребрами без отриц. циклов
// Быстрее Ford-Bellman по константе

ll dist[mxN];
int inq[mxN];
void spfa(int S) {
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
}
