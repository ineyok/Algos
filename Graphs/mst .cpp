// O(m)

// Минимальное остовное дерево
// Алгоритм Крускала

struct DSU {
    ...
};

int n;
vector<vector<int>> edges;

ll kruskal() {
    DSU dsu(n);
    sort(all(edges), [&](vector<int> & a, vector<int> & b) {
        return a[2] < b[2];
    });
    ll sum = 0;
    for(auto & el : edges) {
        int a = el[0], b = el[1], w = el[2];
        if(!dsu.connect(a, b)) {
            sum += w;
            dsu.merge(a, b);
        }
    }
    return sum;
}
