// O(1) на запрос

// ? min на отрезке (теперь можно любую фунцию)

struct Disjoint_sparse {
    int n;
    vector<vector<int>> table;
    void build(int l, int r, int lvl, vector<int> & ar) {
        int mid = (l + r) / 2;
        for(int i = mid; i >= l; --i) {
            table[lvl][i] = ar[i];
            if(i != mid) table[lvl][i] = min(table[lvl][i], table[lvl][i + 1]);
        }
        for(int i = mid + 1; i <= r; ++i) {
            table[lvl][i] = ar[i];
            if(i != mid + 1) table[lvl][i] = min(table[lvl][i], table[lvl][i - 1]);
        }
        if(l != r) {
            build(l, mid, lvl - 1, ar);
            build(mid + 1, r, lvl - 1, ar);
        }
    }

    Disjoint_sparse(vector<int> & ar) {
        while(__builtin_popcount(size(ar)) != 1)
            ar.push_back(0);
        n = size(ar);
        table.resize(__lg(n) + 1, vector<int>(n, -1));
        build(0, n - 1, size(table) - 1, ar);
    }

    int query(int l, int r) {
        int i = __lg(l ^ r) + 1;
        if(table[i][l] == -1) return table[i][r];
        if(table[i][r] == -1) return table[i][l];
        return min(table[i][l], table[i][r]);
    }
};
